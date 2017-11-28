static void
tunnelConnectedWriteDone(const Comm::ConnectionPointer &conn, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, HERE << conn << ", flag=" << flag);

    if (flag != COMM_OK) {
        *tunnelState->status_ptr = HTTP_INTERNAL_SERVER_ERROR;
        tunnelErrorComplete(conn->fd, data, 0);
        return;
    }

    tunnelStartShoveling(tunnelState);
}