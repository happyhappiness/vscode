static void
tunnelClientClosed(const CommCloseCbParams &params)
{
    TunnelStateData *tunnelState = (TunnelStateData *)params.data;
    debugs(26, 3, HERE << tunnelState->client.conn);
    tunnelState->client.conn = NULL;

    if (tunnelState->noConnections()) {
        tunnelStateFree(tunnelState);
        return;
    }

    if (!tunnelState->client.len) {
        tunnelState->server.conn->close();
        return;
    }
}