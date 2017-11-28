void
switchToTunnel(HttpRequest *request, Comm::ConnectionPointer &clientConn, Comm::ConnectionPointer &srvConn)
{
    debugs(26,5, "Revert to tunnel FD " << clientConn->fd << " with FD " << srvConn->fd);
    /* Create state structure. */
    TunnelStateData *tunnelState = NULL;
    const char *url = urlCanonical(request);

    debugs(26, 3, request->method << " " << url << " " << request->http_ver);
    ++statCounter.server.all.requests;
    ++statCounter.server.other.requests;

    tunnelState = new TunnelStateData;
    tunnelState->url = xstrdup(url);
    tunnelState->request = request;
    tunnelState->server.size_ptr = NULL; //Set later if ClientSocketContext is available

    // Temporary static variable to store the unneeded for our case status code
    static int status_code = 0;
    tunnelState->status_ptr = &status_code;
    tunnelState->client.conn = clientConn;

    ConnStateData *conn;
    if ((conn = request->clientConnectionManager.get())) {
        ClientSocketContext::Pointer context = conn->getCurrentContext();
        if (context != NULL && context->http != NULL) {
            tunnelState->logTag_ptr = &context->http->logType;
            tunnelState->server.size_ptr = &context->http->out.size;
            if (context->http->al != NULL) {
                tunnelState->al = context->http->al;
                tunnelState->client.size_ptr = &context->http->al->http.clientRequestSz.payloadData;
            }

#if USE_DELAY_POOLS
            /* no point using the delayIsNoDelay stuff since tunnel is nice and simple */
            if (srvConn->getPeer() && srvConn->getPeer()->options.no_delay)
                tunnelState->server.setDelayId(DelayId::DelayClient(context->http));
#endif
        }
    }

    comm_add_close_handler(tunnelState->client.conn->fd,
                           tunnelClientClosed,
                           tunnelState);

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(tunnelState->client.conn, Config.Timeout.lifetime, timeoutCall);
    fd_table[clientConn->fd].read_method = &default_read_method;
    fd_table[clientConn->fd].write_method = &default_write_method;

    tunnelState->request->hier.note(srvConn, tunnelState->getHost());

    tunnelState->server.conn = srvConn;
    tunnelState->request->peer_host = srvConn->getPeer() ? srvConn->getPeer()->host : NULL;
    comm_add_close_handler(srvConn->fd, tunnelServerClosed, tunnelState);

    debugs(26, 4, "determine post-connect handling pathway.");
    if (srvConn->getPeer()) {
        tunnelState->request->peer_login = srvConn->getPeer()->login;
        tunnelState->request->peer_domain = srvConn->getPeer()->domain;
        tunnelState->request->flags.proxying = !(srvConn->getPeer()->options.originserver);
    } else {
        tunnelState->request->peer_login = NULL;
        tunnelState->request->peer_domain = NULL;
        tunnelState->request->flags.proxying = false;
    }

    timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                             CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(srvConn, Config.Timeout.read, timeoutCall);
    fd_table[srvConn->fd].read_method = &default_read_method;
    fd_table[srvConn->fd].write_method = &default_write_method;

    SSL *ssl = fd_table[srvConn->fd].ssl;
    assert(ssl);
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(b->ptr);
    const MemBuf &buf = srvBio->rBufData();

    AsyncCall::Pointer call = commCbCall(5,5, "tunnelConnectedWriteDone",
                                         CommIoCbPtrFun(tunnelConnectedWriteDone, tunnelState));
    tunnelState->client.write(buf.content(), buf.contentSize(), call, NULL);
}