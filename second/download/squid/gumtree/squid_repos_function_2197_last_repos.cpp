static void
tunnelServerClosed(const CommCloseCbParams &params)
{
    TunnelStateData *tunnelState = (TunnelStateData *)params.data;
    debugs(26, 3, HERE << tunnelState->server.conn);
    tunnelState->server.conn = NULL;
    tunnelState->server.writer = NULL;

    if (tunnelState->request != NULL)
        tunnelState->request->hier.stopPeerClock(false);

    if (tunnelState->noConnections()) {
        // ConnStateData pipeline should contain the CONNECT we are performing
        // but it may be invalid already (bug 4392)
        if (tunnelState->http.valid() && tunnelState->http->getConn()) {
            auto ctx = tunnelState->http->getConn()->pipeline.front();
            if (ctx != nullptr)
                ctx->finished();
        }
        delete tunnelState;
        return;
    }

    if (!tunnelState->client.writer) {
        tunnelState->client.conn->close();
        return;
    }
}