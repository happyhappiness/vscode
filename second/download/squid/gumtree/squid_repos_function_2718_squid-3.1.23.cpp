static void
tunnelConnectDone(int fdnotused, const DnsLookupDetails &dns, comm_err_t status, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    HttpRequest *request = tunnelState->request;
    ErrorState *err = NULL;

    request->recordLookup(dns);

    if (tunnelState->servers->_peer)
        hierarchyNote(&tunnelState->request->hier, tunnelState->servers->code,
                      tunnelState->servers->_peer->name);
    else if (Config.onoff.log_ip_on_direct)
        hierarchyNote(&tunnelState->request->hier, tunnelState->servers->code,
                      fd_table[tunnelState->server.fd()].ipaddr);
    else
        hierarchyNote(&tunnelState->request->hier, tunnelState->servers->code,
                      tunnelState->host);

    if (status == COMM_ERR_DNS) {
        debugs(26, 4, "tunnelConnect: Unknown host: " << tunnelState->host);
        err = errorCon(ERR_DNS_FAIL, HTTP_NOT_FOUND, request);
        *tunnelState->status_ptr = HTTP_NOT_FOUND;
        err->dnsError = dns.error;
        err->callback = tunnelErrorComplete;
        err->callback_data = tunnelState;
        errorSend(tunnelState->client.fd(), err);
    } else if (status != COMM_OK) {
        err = errorCon(ERR_CONNECT_FAIL, HTTP_SERVICE_UNAVAILABLE, request);
        *tunnelState->status_ptr = HTTP_SERVICE_UNAVAILABLE;
        err->xerrno = xerrno;
        err->port = tunnelState->port;
        err->callback = tunnelErrorComplete;
        err->callback_data = tunnelState;
        errorSend(tunnelState->client.fd(), err);
    } else {
        if (tunnelState->servers->_peer && !tunnelState->servers->_peer->options.originserver)
            tunnelProxyConnected(tunnelState->server.fd(), tunnelState);
        else {
            tunnelConnected(tunnelState->server.fd(), tunnelState);
        }

        commSetTimeout(tunnelState->server.fd(),
                       Config.Timeout.read,
                       tunnelTimeout,
                       tunnelState);
    }
}