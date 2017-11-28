}

static void
tunnelRelayConnectRequest(const Comm::ConnectionPointer &srv, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert(!tunnelState->waitingForConnectExchange());
    HttpHeader hdr_out(hoRequest);
    Packer p;
    HttpStateFlags flags;
    debugs(26, 3, HERE << srv << ", tunnelState=" << tunnelState);
    memset(&flags, '\0', sizeof(flags));
    flags.proxying = tunnelState->request->flags.proxying;
    MemBuf mb;
    mb.init();
    mb.Printf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
    HttpStateData::httpBuildRequestHeader(tunnelState->request.getRaw(),
                                          NULL,			/* StoreEntry */
                                          tunnelState->al,			/* AccessLogEntry */
                                          &hdr_out,
                                          flags);			/* flags */
    packerToMemInit(&p, &mb);
    hdr_out.packInto(&p);
    hdr_out.clean();
    packerClean(&p);
    mb.append("\r\n", 2);

    debugs(11, 2, "Tunnel Server REQUEST: " << tunnelState->server.conn << ":\n----------\n" <<
           Raw("tunnelRelayConnectRequest", mb.content(), mb.contentSize()) << "\n----------");

    if (tunnelState->clientExpectsConnectResponse()) {
        // hack: blindly tunnel peer response (to our CONNECT request) to the client as ours.
        AsyncCall::Pointer writeCall = commCbCall(5,5, "tunnelConnectedWriteDone",
                                       CommIoCbPtrFun(tunnelConnectedWriteDone, tunnelState));
        Comm::Write(srv, &mb, writeCall);
    } else {
        // we have to eat the connect response from the peer (so that the client
        // does not see it) and only then start shoveling data to the client
        AsyncCall::Pointer writeCall = commCbCall(5,5, "tunnelConnectReqWriteDone",
                                       CommIoCbPtrFun(tunnelConnectReqWriteDone,
                                                      tunnelState));
        Comm::Write(srv, &mb, writeCall);
        tunnelState->connectReqWriting = true;

        tunnelState->connectRespBuf = new MemBuf;
        // SQUID_TCP_SO_RCVBUF: we should not accumulate more than regular I/O buffer
        // can hold since any CONNECT response leftovers have to fit into server.buf.
        // 2*SQUID_TCP_SO_RCVBUF: HttpMsg::parse() zero-terminates, which uses space.
        tunnelState->connectRespBuf->init(SQUID_TCP_SO_RCVBUF, 2*SQUID_TCP_SO_RCVBUF);
        tunnelState->readConnectResponse();

        assert(tunnelState->waitingForConnectExchange());
    }

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(srv, Config.Timeout.read, timeoutCall);
}

