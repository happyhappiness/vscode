void
TunnelStateData::informUserOfPeerError(const char *errMsg)
{
    server.len = 0;
    if (!clientExpectsConnectResponse()) {
        // closing the connection is the best we can do here
        debugs(50, 3, server.conn << " closing on error: " << errMsg);
        server.conn->close();
        return;
    }
    ErrorState *err  = new ErrorState(ERR_CONNECT_FAIL, Http::scBadGateway, request.getRaw());
    err->callback = tunnelErrorComplete;
    err->callback_data = this;
    *status_ptr = Http::scBadGateway;
    errorSend(http->getConn()->clientConnection, err);
}