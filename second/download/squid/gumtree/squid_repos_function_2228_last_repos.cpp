static void
tunnelConnectedWriteDone(const Comm::ConnectionPointer &conn, char *, size_t len, Comm::Flag flag, int, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, HERE << conn << ", flag=" << flag);
    tunnelState->client.writer = NULL;

    if (flag != Comm::OK) {
        *tunnelState->status_ptr = Http::scInternalServerError;
        tunnelErrorComplete(conn->fd, data, 0);
        return;
    }

    if (auto http = tunnelState->http.get()) {
        http->out.headers_sz += len;
        http->out.size += len;
    }

    tunnelStartShoveling(tunnelState);
}