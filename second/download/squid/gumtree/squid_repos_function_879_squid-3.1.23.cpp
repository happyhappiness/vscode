int commSetTimeout(int fd, int timeout, AsyncCall::Pointer &callback)
{
    debugs(5, 3, HERE << "FD " << fd << " timeout " << timeout);
    assert(fd >= 0);
    assert(fd < Squid_MaxFD);
    fde *F = &fd_table[fd];
    assert(F->flags.open);

    if (timeout < 0) {
        F->timeoutHandler = NULL;
        F->timeout = 0;
    } else {
        if (callback != NULL) {
            typedef CommTimeoutCbParams Params;
            Params &params = GetCommParams<Params>(callback);
            params.fd = fd;
            F->timeoutHandler = callback;
        }

        F->timeout = squid_curtime + (time_t) timeout;
    }

    return F->timeout;

}