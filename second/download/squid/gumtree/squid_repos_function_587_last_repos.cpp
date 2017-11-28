void
comm_close_complete(const FdeCbParams &params)
{
    fde *F = &fd_table[params.fd];
    F->ssl.reset();
    F->dynamicTlsContext.reset();
    fd_close(params.fd);        /* update fdstat */
    close(params.fd);

    ++ statCounter.syscalls.sock.closes;

    /* When one connection closes, give accept() a chance, if need be */
    Comm::AcceptLimiter::Instance().kick();
}