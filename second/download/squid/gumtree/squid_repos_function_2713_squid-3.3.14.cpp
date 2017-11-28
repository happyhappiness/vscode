static void
tunnelStartShoveling(TunnelStateData *tunnelState)
{
    *tunnelState->status_ptr = HTTP_OK;
    if (cbdataReferenceValid(tunnelState)) {
        tunnelState->copyRead(tunnelState->server, TunnelStateData::ReadServer);
        tunnelState->copyRead(tunnelState->client, TunnelStateData::ReadClient);
    }
}