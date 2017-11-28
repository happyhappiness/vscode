static void
tunnelProxyConnected(int fd, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    HttpHeader hdr_out(hoRequest);
    Packer p;
    http_state_flags flags;
    debugs(26, 3, "tunnelProxyConnected: FD " << fd << " tunnelState=" << tunnelState);
    memset(&flags, '\0', sizeof(flags));
    flags.proxying = tunnelState->request->flags.proxying;
    MemBuf mb;
    mb.init();
    mb.Printf("CONNECT %s HTTP/1.1\r\n", tunnelState->url);
    HttpStateData::httpBuildRequestHeader(tunnelState->request,
                                          tunnelState->request,
                                          NULL,			/* StoreEntry */
                                          &hdr_out,
                                          flags);			/* flags */
    packerToMemInit(&p, &mb);
    hdr_out.packInto(&p);
    hdr_out.clean();
    packerClean(&p);
    mb.append("\r\n", 2);

    comm_write_mbuf(tunnelState->server.fd(), &mb, tunnelProxyConnectedWriteDone, tunnelState);
    commSetTimeout(tunnelState->server.fd(), Config.Timeout.read, tunnelTimeout, tunnelState);
}