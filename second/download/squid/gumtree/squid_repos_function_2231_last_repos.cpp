static void
tunnelConnected(const Comm::ConnectionPointer &server, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, HERE << server << ", tunnelState=" << tunnelState);

    if (!tunnelState->clientExpectsConnectResponse())
        tunnelStartShoveling(tunnelState); // ssl-bumped connection, be quiet
    else {
        AsyncCall::Pointer call = commCbCall(5,5, "tunnelConnectedWriteDone",
                                             CommIoCbPtrFun(tunnelConnectedWriteDone, tunnelState));
        tunnelState->client.write(conn_established, strlen(conn_established), call, NULL);
    }
}