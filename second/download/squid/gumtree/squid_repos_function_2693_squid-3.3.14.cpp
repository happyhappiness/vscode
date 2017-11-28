static void
tunnelServerClosed(const CommCloseCbParams &params)
{
    TunnelStateData *tunnelState = (TunnelStateData *)params.data;
    debugs(26, 3, HERE << tunnelState->server.conn);
    tunnelState->server.conn = NULL;

    if (tunnelState->noConnections()) {
        tunnelStateFree(tunnelState);
        return;
    }

    if (!tunnelState->server.len) {
        tunnelState->client.conn->close();
        return;
    }
}