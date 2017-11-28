void
switchToTunnel(HttpRequest *request, Comm::ConnectionPointer &clientConn, Comm::ConnectionPointer &srvConn)
{
    debugs(26,5, "Revert to tunnel FD " << clientConn->fd << " with FD " << srvConn->fd);

    /* Create state structure. */
    ++statCounter.server.all.requests;
    ++statCounter.server.other.requests;

    auto conn = request->clientConnectionManager.get();
    Must(conn);
    Http::StreamPointer context = conn->pipeline.front();
    Must(context && context->http);

    debugs(26, 3, request->method << " " << context->http->uri << " " << request->http_ver);

    TunnelStateData *tunnelState = new TunnelStateData(context->http);

    fd_table[clientConn->fd].read_method = &default_read_method;
    fd_table[clientConn->fd].write_method = &default_write_method;

    request->hier.note(srvConn, tunnelState->getHost());

    tunnelState->server.conn = srvConn;

#if USE_DELAY_POOLS
    /* no point using the delayIsNoDelay stuff since tunnel is nice and simple */
    if (srvConn->getPeer() && srvConn->getPeer()->options.no_delay)
        tunnelState->server.setDelayId(DelayId::DelayClient(context->http));
#endif

    request->peer_host = srvConn->getPeer() ? srvConn->getPeer()->host : nullptr;
    comm_add_close_handler(srvConn->fd, tunnelServerClosed, tunnelState);

    debugs(26, 4, "determine post-connect handling pathway.");
    if (srvConn->getPeer()) {
        request->peer_login = srvConn->getPeer()->login;
        request->peer_domain = srvConn->getPeer()->domain;
        request->flags.auth_no_keytab = srvConn->getPeer()->options.auth_no_keytab;
        request->flags.proxying = !(srvConn->getPeer()->options.originserver);
    } else {
        request->peer_login = nullptr;
        request->peer_domain = nullptr;
        request->flags.auth_no_keytab = false;
        request->flags.proxying = false;
    }

    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "tunnelTimeout",
                                     CommTimeoutCbPtrFun(tunnelTimeout, tunnelState));
    commSetConnTimeout(srvConn, Config.Timeout.read, timeoutCall);
    fd_table[srvConn->fd].read_method = &default_read_method;
    fd_table[srvConn->fd].write_method = &default_write_method;

    auto ssl = fd_table[srvConn->fd].ssl.get();
    assert(ssl);
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));
    tunnelState->preReadServerData = srvBio->rBufData();
    tunnelStartShoveling(tunnelState);
}