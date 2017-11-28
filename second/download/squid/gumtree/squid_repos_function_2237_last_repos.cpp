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
                                   CommIoCbPtrFun(tunnelConnectReqWriteDone,
                                           tunnelState));

    tunnelState->server.write(mb.buf, mb.size, writeCall, mb.freeFunc());
    tunnelState->connectReqWriting = true;

    tunnelState->connectRespBuf = new MemBuf;
    // SQUID_TCP_SO_RCVBUF: we should not accumulate more than regular I/O buffer
    // can hold since any CONNECT response leftovers have to fit into server.buf.
    // 2*SQUID_TCP_SO_RCVBUF: HttpMsg::parse() zero-terminates, which uses space.
    tunnelState->connectRespBuf->init(SQUID_TCP_SO_RCVBUF, 2*SQUID_TCP_SO_RCVBUF);
    tunnelState->readConnectResponse();

    assert(tunnelState->waitingForConnectExchange());

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(srv, Config.Timeout.read, timeoutCall);
}