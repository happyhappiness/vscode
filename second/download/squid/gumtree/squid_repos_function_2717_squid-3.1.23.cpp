static void
tunnelErrorComplete(int fdnotused, void *data, size_t sizenotused)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    assert(tunnelState != NULL);
    /* temporary lock to save our own feets (comm_close -> tunnelClientClosed -> Free) */
    cbdataInternalLock(tunnelState);

    if (!fd_closed(tunnelState->client.fd()))
        comm_close(tunnelState->client.fd());

    if (!fd_closed(tunnelState->server.fd()))
        comm_close(tunnelState->server.fd());

    cbdataInternalUnlock(tunnelState);
}