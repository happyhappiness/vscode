static void
tunnelConnectedWriteDone(const Comm::ConnectionPointer &conn, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, HERE << conn << ", flag=" << flag);
    tunnelState->client.writer = NULL;

    if (flag != COMM_OK) {
        *tunnelState->status_ptr = Http::scInternalServerError;
        tunnelErrorComplete(conn->fd, data, 0);
        return;
    }

    tunnelStartShoveling(tunnelState);
}