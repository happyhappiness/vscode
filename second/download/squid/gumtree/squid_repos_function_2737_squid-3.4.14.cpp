static void
tunnelClientClosed(const CommCloseCbParams &params)
{
    TunnelStateData *tunnelState = (TunnelStateData *)params.data;
    debugs(26, 3, HERE << tunnelState->client.conn);
    tunnelState->client.conn = NULL;
    tunnelState->client.writer = NULL;

    if (tunnelState->noConnections()) {
        delete tunnelState;
        return;
    }

    if (!tunnelState->server.writer) {
        tunnelState->server.conn->close();
        return;
    }
}