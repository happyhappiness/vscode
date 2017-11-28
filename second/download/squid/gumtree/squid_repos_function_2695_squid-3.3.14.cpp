static void
tunnelStateFree(TunnelStateData * tunnelState)
{
    debugs(26, 3, HERE << "tunnelState=" << tunnelState);
    assert(tunnelState != NULL);
    assert(tunnelState->noConnections());
    safe_free(tunnelState->url);
    tunnelState->serverDestinations.clean();
    HTTPMSGUNLOCK(tunnelState->request);
    delete tunnelState;
}