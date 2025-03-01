}

static void
tunnelRelayConnectRequest(const Comm::ConnectionPointer &srv, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    HttpHeader hdr_out(hoRequest);
    Packer p;
    HttpStateFlags flags;
    debugs(26, 3, HERE << srv << ", tunnelState=" << tunnelState);
    memset(&flags, '\0', sizeof(flags));
    flags.proxying = tunnelState->request->flags.proxying;
    MemBuf mb;
    mb.init();
    mb.Printf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
    HttpStateData::httpBuildRequestHeader(tunnelState->request,
                                          NULL,			/* StoreEntry */
                                          tunnelState->al,			/* AccessLogEntry */
                                          &hdr_out,
                                          flags);			/* flags */
    packerToMemInit(&p, &mb);
    hdr_out.packInto(&p);
    hdr_out.clean();
    packerClean(&p);
    mb.append("\r\n", 2);

    AsyncCall::Pointer writeCall = commCbCall(5,5, "tunnelConnectedWriteDone",
                                   CommIoCbPtrFun(tunnelConnectedWriteDone, tunnelState));
    Comm::Write(srv, &mb, writeCall);

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(srv, Config.Timeout.read, timeoutCall);
}

