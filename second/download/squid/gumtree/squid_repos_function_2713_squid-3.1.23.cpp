static void
tunnelConnectTimeout(int fd, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    HttpRequest *request = tunnelState->request;
    ErrorState *err = NULL;

    if (tunnelState->servers) {
        if (tunnelState->servers->_peer)
            hierarchyNote(&tunnelState->request->hier, tunnelState->servers->code,
                          tunnelState->servers->_peer->name);
        else if (Config.onoff.log_ip_on_direct)
            hierarchyNote(&tunnelState->request->hier, tunnelState->servers->code,
                          fd_table[tunnelState->server.fd()].ipaddr);
        else
            hierarchyNote(&tunnelState->request->hier, tunnelState->servers->code,
                          tunnelState->host);
    } else
        debugs(26, 1, "tunnelConnectTimeout(): tunnelState->servers is NULL");

    err = errorCon(ERR_CONNECT_FAIL, HTTP_SERVICE_UNAVAILABLE, request);

    *tunnelState->status_ptr = HTTP_SERVICE_UNAVAILABLE;

    err->xerrno = ETIMEDOUT;

    err->port = tunnelState->port;

    err->callback = tunnelErrorComplete;

    err->callback_data = tunnelState;

    errorSend(tunnelState->client.fd(), err);
    comm_close(fd);
}