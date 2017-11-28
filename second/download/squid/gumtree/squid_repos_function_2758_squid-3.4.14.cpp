static void
tunnelTimeout(const CommTimeoutCbParams &io)
{
    TunnelStateData *tunnelState = static_cast<TunnelStateData *>(io.data);
    debugs(26, 3, HERE << io.conn);
    /* Temporary lock to protect our own feets (comm_close -> tunnelClientClosed -> Free) */
    CbcPointer<TunnelStateData> safetyLock(tunnelState);

    tunnelState->client.closeIfOpen();
    tunnelState->server.closeIfOpen();
}