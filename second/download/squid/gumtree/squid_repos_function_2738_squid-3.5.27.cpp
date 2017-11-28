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
        delete tunnelState;
        return;
    }

    if (!tunnelState->client.writer) {
        tunnelState->client.conn->close();
        return;
    }
}