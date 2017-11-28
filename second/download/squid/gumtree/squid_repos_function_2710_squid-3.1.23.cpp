static void
tunnelTimeout(int fd, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, "tunnelTimeout: FD " << fd);
    /* Temporary lock to protect our own feets (comm_close -> tunnelClientClosed -> Free) */
    cbdataInternalLock(tunnelState);

    tunnelState->client.closeIfOpen();
    tunnelState->server.closeIfOpen();
    cbdataInternalUnlock(tunnelState);
}