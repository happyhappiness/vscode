static void
tunnelConnectedWriteDone(const Comm::ConnectionPointer &conn, char *buf, size_t size, Comm::Flag flag, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;
    debugs(26, 3, HERE << conn << ", flag=" << flag);
    tunnelState->client.writer = NULL;

    if (flag != Comm::OK) {
        *tunnelState->status_ptr = Http::scInternalServerError;
        tunnelErrorComplete(conn->fd, data, 0);
        return;
    }

    if (ClientHttpRequest *http = tunnelState->http.get()) {
        http->out.headers_sz += size;
        http->out.size += size;
    }

    tunnelStartShoveling(tunnelState);
}