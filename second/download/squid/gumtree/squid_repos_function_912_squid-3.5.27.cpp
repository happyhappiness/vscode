void
comm_lingering_close(int fd)
{
#if USE_OPENSSL
    if (fd_table[fd].ssl)
        ssl_shutdown_method(fd_table[fd].ssl);
#endif

    if (shutdown(fd, 1) < 0) {
        comm_close(fd);
        return;
    }

    fd_note(fd, "lingering close");
    AsyncCall::Pointer call = commCbCall(5,4, "commLingerTimeout", FdeCbPtrFun(commLingerTimeout, NULL));

    debugs(5, 3, HERE << "FD " << fd << " timeout " << timeout);
    assert(fd_table[fd].flags.open);
    if (callback != NULL) {
        typedef FdeCbParams Params;
        Params &params = GetCommParams<Params>(callback);
        params.fd = fd;
        fd_table[fd].timeoutHandler = callback;
        fd_table[fd].timeout = squid_curtime + static_cast<time_t>(10);
    }

    Comm::SetSelect(fd, COMM_SELECT_READ, commLingerClose, NULL, 0);
}