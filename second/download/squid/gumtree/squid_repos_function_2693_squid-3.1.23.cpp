static void
tunnelServerClosed(int fd, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, "tunnelServerClosed: FD " << fd);
    assert(fd == tunnelState->server.fd());
    tunnelState->server.fd(-1);

    if (tunnelState->noConnections()) {
        tunnelStateFree(tunnelState);
        return;
    }

    if (!tunnelState->server.len) {
        comm_close(tunnelState->client.fd());
        return;
    }
}