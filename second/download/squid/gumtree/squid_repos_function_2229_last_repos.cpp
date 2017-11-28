static void
tunnelConnectReqWriteDone(const Comm::ConnectionPointer &conn, char *, size_t, Comm::Flag flag, int, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, conn << ", flag=" << flag);
    tunnelState->server.writer = NULL;
    assert(tunnelState->waitingForConnectRequest());

    if (flag != Comm::OK) {
        *tunnelState->status_ptr = Http::scInternalServerError;
        tunnelErrorComplete(conn->fd, data, 0);
        return;
    }

    tunnelState->connectReqWriting = false;
    tunnelState->connectExchangeCheckpoint();
}