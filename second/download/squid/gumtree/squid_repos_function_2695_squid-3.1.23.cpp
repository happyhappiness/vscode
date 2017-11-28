static void
tunnelStateFree(TunnelStateData * tunnelState)
{
    debugs(26, 3, "tunnelStateFree: tunnelState=" << tunnelState);
    assert(tunnelState != NULL);
    assert(tunnelState->noConnections());
    safe_free(tunnelState->url);
    FwdState::serversFree(&tunnelState->servers);
    safe_free(tunnelState->host);
    HTTPMSGUNLOCK(tunnelState->request);
    delete tunnelState;
}