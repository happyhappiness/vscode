static void
tunnelConnected(int fd, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, "tunnelConnected: FD " << fd << " tunnelState=" << tunnelState);
    *tunnelState->status_ptr = HTTP_OK;
    comm_write(tunnelState->client.fd(), conn_established, strlen(conn_established),
               tunnelConnectedWriteDone, tunnelState, NULL);
}