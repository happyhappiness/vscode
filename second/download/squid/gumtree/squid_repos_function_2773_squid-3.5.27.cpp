void
tunnelStart(ClientHttpRequest * http)
{
    debugs(26, 3, HERE);
    /* Create state structure. */
    TunnelStateData *tunnelState = NULL;
    ErrorState *err = NULL;
    HttpRequest *request = http->request;
    char *url = http->uri;

    /*
     * client_addr.isNoAddr()  indicates this is an "internal" request
     * from peer_digest.c, asn.c, netdb.c, etc and should always
     * be allowed.  yuck, I know.
     */

    if (Config.accessList.miss && !request->client_addr.isNoAddr()) {
        /*
         * Check if this host is allowed to fetch MISSES from us (miss_access)
         * default is to allow.
         */
        ACLFilledChecklist ch(Config.accessList.miss, request, NULL);
        ch.src_addr = request->client_addr;
        ch.my_addr = request->my_addr;
        if (ch.fastCheck() == ACCESS_DENIED) {
            debugs(26, 4, HERE << "MISS access forbidden.");
            err = new ErrorState(ERR_FORWARDING_DENIED, Http::scForbidden, request);
            http->al->http.code = Http::scForbidden;
            errorSend(http->getConn()->clientConnection, err);
            return;
        }
    }

    debugs(26, 3, request->method << ' ' << url << ' ' << request->http_ver);
    ++statCounter.server.all.requests;
    ++statCounter.server.other.requests;

    tunnelState = new TunnelStateData;
#if USE_DELAY_POOLS
    tunnelState->server.setDelayId(DelayId::DelayClient(http));
#endif
    tunnelState->url = xstrdup(url);
    tunnelState->request = request;
    tunnelState->server.size_ptr = &http->out.size;
    tunnelState->client.size_ptr = &http->al->http.clientRequestSz.payloadData;
    tunnelState->status_ptr = &http->al->http.code;
    tunnelState->logTag_ptr = &http->logType;
    tunnelState->client.conn = http->getConn()->clientConnection;
    tunnelState->http = http;
    tunnelState->al = http->al ;
    tunnelState->started = squid_curtime;

    comm_add_close_handler(tunnelState->client.conn->fd,
                           tunnelClientClosed,
                           tunnelState);

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(tunnelState->client.conn, Config.Timeout.lifetime, timeoutCall);

    peerSelect(&(tunnelState->serverDestinations), request, tunnelState->al,
               NULL,
               tunnelPeerSelectComplete,
               tunnelState);
}