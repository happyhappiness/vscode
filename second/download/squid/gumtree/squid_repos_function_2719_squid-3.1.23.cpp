void
tunnelStart(ClientHttpRequest * http, int64_t * size_ptr, int *status_ptr)
{
    /* Create state structure. */
    TunnelStateData *tunnelState = NULL;
    int sock;
    ErrorState *err = NULL;
    int answer;
    int fd = http->getConn()->fd;
    HttpRequest *request = http->request;
    char *url = http->uri;
    /*
     * client_addr.IsNoAddr()  indicates this is an "internal" request
     * from peer_digest.c, asn.c, netdb.c, etc and should always
     * be allowed.  yuck, I know.
     */

    if (!request->client_addr.IsNoAddr() && Config.accessList.miss) {
        /*
         * Check if this host is allowed to fetch MISSES from us (miss_access)
         * default is to allow.
         */
        ACLFilledChecklist ch(Config.accessList.miss, request, NULL);
        ch.src_addr = request->client_addr;
        ch.my_addr = request->my_addr;
        answer = ch.fastCheck();

        if (answer == 0) {
            err = errorCon(ERR_FORWARDING_DENIED, HTTP_FORBIDDEN, request);
            *status_ptr = HTTP_FORBIDDEN;
            errorSend(fd, err);
            return;
        }
    }

    debugs(26, 3, "tunnelStart: '" << RequestMethodStr(request->method) << " " << url << "'");
    statCounter.server.all.requests++;
    statCounter.server.other.requests++;
    /* Create socket. */
    IpAddress temp = getOutgoingAddr(request,NULL);

    // if IPv6 is disabled try to force IPv4-only outgoing.
    if (!Ip::EnableIpv6 && !temp.SetIPv4()) {
        debugs(50, 4, "tunnelStart: IPv6 is Disabled. Tunnel failed from " << temp);
        ErrorState *anErr = errorCon(ERR_CONNECT_FAIL, HTTP_SERVICE_UNAVAILABLE, request);
        anErr->xerrno = EAFNOSUPPORT;
        errorSend(fd, anErr);
        return;
    }

    // if IPv6 is split-stack, prefer IPv4
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK) {
        // NP: This is not a great choice of default,
        // but with the current Internet being IPv4-majority has a higher success rate.
        // if setting to IPv4 fails we dont care, that just means to use IPv6 outgoing.
        temp.SetIPv4();
    }

    int flags = COMM_NONBLOCKING;
    if (request->flags.spoof_client_ip) {
        flags |= COMM_TRANSPARENT;
    }
    sock = comm_openex(SOCK_STREAM,
                       IPPROTO_TCP,
                       temp,
                       flags,
                       getOutgoingTOS(request),
                       url);

    if (sock == COMM_ERROR) {
        debugs(26, 4, "tunnelStart: Failed because we're out of sockets.");
        err = errorCon(ERR_SOCKET_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
        *status_ptr = HTTP_INTERNAL_SERVER_ERROR;
        err->xerrno = errno;
        errorSend(fd, err);
        return;
    }

    // record local IP:port for %<la and %<lp logging
    if (comm_local_port(sock))
        request->hier.peer_local_addr = fd_table[sock].local_addr;

    tunnelState = new TunnelStateData;
#if DELAY_POOLS

    tunnelState->server.setDelayId(DelayId::DelayClient(http));
#endif

    tunnelState->url = xstrdup(url);
    tunnelState->request = HTTPMSGLOCK(request);
    tunnelState->server.size_ptr = size_ptr;
    tunnelState->status_ptr = status_ptr;
    tunnelState->client.fd(fd);
    tunnelState->server.fd(sock);
    comm_add_close_handler(tunnelState->server.fd(),
                           tunnelServerClosed,
                           tunnelState);
    comm_add_close_handler(tunnelState->client.fd(),
                           tunnelClientClosed,
                           tunnelState);
    commSetTimeout(tunnelState->client.fd(),
                   Config.Timeout.lifetime,
                   tunnelTimeout,
                   tunnelState);
    commSetTimeout(tunnelState->server.fd(),
                   Config.Timeout.connect,
                   tunnelConnectTimeout,
                   tunnelState);
    peerSelect(request,
               NULL,
               tunnelPeerSelectComplete,
               tunnelState);
}