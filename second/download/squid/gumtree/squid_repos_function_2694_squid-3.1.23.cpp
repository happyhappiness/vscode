static void
tunnelClientClosed(int fd, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, "tunnelClientClosed: FD " << fd);
    assert(fd == tunnelState->client.fd());
    tunnelState->client.fd(-1);

    if (tunnelState->noConnections()) {
        tunnelStateFree(tunnelState);
        return;
    }

    if (!tunnelState->client.len) {
        comm_close(tunnelState->server.fd());
        return;
    }
}