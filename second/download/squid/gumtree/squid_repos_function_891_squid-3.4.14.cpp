int
commSetConnTimeout(const Comm::ConnectionPointer &conn, int timeout, AsyncCall::Pointer &callback)
{
    debugs(5, 3, HERE << conn << " timeout " << timeout);
    assert(Comm::IsConnOpen(conn));
    assert(conn->fd < Squid_MaxFD);
    fde *F = &fd_table[conn->fd];
    assert(F->flags.open);

    if (timeout < 0) {
        F->timeoutHandler = NULL;
        F->timeout = 0;
    } else {
        if (callback != NULL) {
            typedef CommTimeoutCbParams Params;
            Params &params = GetCommParams<Params>(callback);
            params.conn = conn;
            F->timeoutHandler = callback;
        }

        F->timeout = squid_curtime + (time_t) timeout;
    }

    return F->timeout;
}