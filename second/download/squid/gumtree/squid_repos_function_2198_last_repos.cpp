static void
tunnelClientClosed(const CommCloseCbParams &params)
{
    TunnelStateData *tunnelState = (TunnelStateData *)params.data;
    debugs(26, 3, HERE << tunnelState->client.conn);
    tunnelState->client.conn = NULL;
    tunnelState->client.writer = NULL;

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

    if (!tunnelState->server.writer) {
        tunnelState->server.conn->close();
        return;
    }
}