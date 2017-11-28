static void
tunnelPeerSelectComplete(FwdServer * fs, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    HttpRequest *request = tunnelState->request;
    peer *g = NULL;

    if (fs == NULL) {
        ErrorState *err;
        err = errorCon(ERR_CANNOT_FORWARD, HTTP_SERVICE_UNAVAILABLE, request);
        *tunnelState->status_ptr = HTTP_SERVICE_UNAVAILABLE;
        err->callback = tunnelErrorComplete;
        err->callback_data = tunnelState;
        errorSend(tunnelState->client.fd(), err);
        return;
    }

    tunnelState->servers = fs;
    tunnelState->host = fs->_peer ? xstrdup(fs->_peer->host) : xstrdup(request->GetHost());

    if (fs->_peer == NULL) {
        tunnelState->port = request->port;
    } else if (fs->_peer->http_port != 0) {
        tunnelState->port = fs->_peer->http_port;
    } else if ((g = peerFindByName(fs->_peer->host))) {
        tunnelState->port = g->http_port;
    } else {
        tunnelState->port = CACHE_HTTP_PORT;
    }

    if (fs->_peer) {
        tunnelState->request->peer_login = fs->_peer->login;
        tunnelState->request->flags.proxying = (fs->_peer->options.originserver?0:1);
    } else {
        tunnelState->request->peer_login = NULL;
        tunnelState->request->flags.proxying = 0;
    }

#if DELAY_POOLS
    /* no point using the delayIsNoDelay stuff since tunnel is nice and simple */
    if (g && g->options.no_delay)
        tunnelState->server.setDelayId(DelayId());

#endif

    commConnectStart(tunnelState->server.fd(),
                     tunnelState->host,
                     tunnelState->port,
                     tunnelConnectDone,
                     tunnelState);
}