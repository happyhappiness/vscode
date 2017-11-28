    }

    debugs(26, 3, request->method << ' ' << url << ' ' << request->http_ver);
    ++statCounter.server.all.requests;
    ++statCounter.server.other.requests;

    tunnelState = new TunnelStateData(http);
#if USE_DELAY_POOLS
    //server.setDelayId called from tunnelConnectDone after server side connection established
#endif

    peerSelect(&(tunnelState->serverDestinations), request, http->al,
               NULL,
               tunnelPeerSelectComplete,
               tunnelState);
}

void
TunnelStateData::connectToPeer()
{
    if (CachePeer *p = server.conn->getPeer()) {
        if (p->secure.encryptTransport) {
            AsyncCall::Pointer callback = asyncCall(5,4,
                                                    "TunnelStateData::ConnectedToPeer",
                                                    MyAnswerDialer(&TunnelStateData::connectedToPeer, this));
            auto *connector = new Security::BlindPeerConnector(request, server.conn, callback, al);
            AsyncJob::Start(connector); // will call our callback
            return;
        }
    }

    Security::EncryptorAnswer nil;
    connectedToPeer(nil);
}

void
TunnelStateData::connectedToPeer(Security::EncryptorAnswer &answer)
{
    if (ErrorState *error = answer.error.get()) {
        *status_ptr = error->httpStatus;
        error->callback = tunnelErrorComplete;
        error->callback_data = this;
        errorSend(client.conn, error);
        answer.error.clear(); // preserve error for errorSendComplete()
        return;
    }

    tunnelRelayConnectRequest(server.conn, this);
}

static void
tunnelRelayConnectRequest(const Comm::ConnectionPointer &srv, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert(!tunnelState->waitingForConnectExchange());
    HttpHeader hdr_out(hoRequest);
    Http::StateFlags flags;
    debugs(26, 3, HERE << srv << ", tunnelState=" << tunnelState);
    memset(&flags, '\0', sizeof(flags));
    flags.proxying = tunnelState->request->flags.proxying;
    MemBuf mb;
    mb.init();
    mb.appendf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
    HttpStateData::httpBuildRequestHeader(tunnelState->request.getRaw(),
                                          NULL,         /* StoreEntry */
                                          tunnelState->al,          /* AccessLogEntry */
                                          &hdr_out,
                                          flags);           /* flags */
    hdr_out.packInto(&mb);
    hdr_out.clean();
    mb.append("\r\n", 2);

    debugs(11, 2, "Tunnel Server REQUEST: " << tunnelState->server.conn <<
           ":\n----------\n" << mb.buf << "\n----------");

    AsyncCall::Pointer writeCall = commCbCall(5,5, "tunnelConnectReqWriteDone",
