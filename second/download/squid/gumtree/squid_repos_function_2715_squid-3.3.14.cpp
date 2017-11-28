static void
tunnelConnected(const Comm::ConnectionPointer &server, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, HERE << server << ", tunnelState=" << tunnelState);

    if (tunnelState->request && (tunnelState->request->flags.spoofClientIp || tunnelState->request->flags.intercepted))
        tunnelStartShoveling(tunnelState); // ssl-bumped connection, be quiet
    else {
        AsyncCall::Pointer call = commCbCall(5,5, "tunnelConnectedWriteDone",
                                             CommIoCbPtrFun(tunnelConnectedWriteDone, tunnelState));
        Comm::Write(tunnelState->client.conn, conn_established, strlen(conn_established), call, NULL);
    }
}