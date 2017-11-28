void
Comm::TcpAcceptor::setListen()
{
    errcode = errno = 0;
    if (listen(conn->fd, Squid_MaxFD >> 2) < 0) {
        errcode = errno;
        debugs(50, DBG_CRITICAL, "ERROR: listen(" << status() << ", " << (Squid_MaxFD >> 2) << "): " << xstrerr(errcode));
        return;
    }

    if (Config.accept_filter && strcmp(Config.accept_filter, "none") != 0) {
#ifdef SO_ACCEPTFILTER
        struct accept_filter_arg afa;
        bzero(&afa, sizeof(afa));
        debugs(5, DBG_IMPORTANT, "Installing accept filter '" << Config.accept_filter << "' on " << conn);
        xstrncpy(afa.af_name, Config.accept_filter, sizeof(afa.af_name));
        if (setsockopt(conn->fd, SOL_SOCKET, SO_ACCEPTFILTER, &afa, sizeof(afa)) < 0)
            debugs(5, DBG_CRITICAL, "WARNING: SO_ACCEPTFILTER '" << Config.accept_filter << "': '" << xstrerror());
#elif defined(TCP_DEFER_ACCEPT)
        int seconds = 30;
        if (strncmp(Config.accept_filter, "data=", 5) == 0)
            seconds = atoi(Config.accept_filter + 5);
        if (setsockopt(conn->fd, IPPROTO_TCP, TCP_DEFER_ACCEPT, &seconds, sizeof(seconds)) < 0)
            debugs(5, DBG_CRITICAL, "WARNING: TCP_DEFER_ACCEPT '" << Config.accept_filter << "': '" << xstrerror());
#else
        debugs(5, DBG_CRITICAL, "WARNING: accept_filter not supported on your OS");
#endif
    }

#if 0
    // Untested code.
    // Set TOS if needed.
    // To correctly implement TOS values on listening sockets, probably requires
    // more work to inherit TOS values to created connection objects.
    if (conn->tos)
        Ip::Qos::setSockTos(conn, conn->tos)
#if SO_MARK
        if (conn->nfmark)
            Ip::Qos::setSockNfmark(conn, conn->nfmark);
#endif
#endif

    typedef CommCbMemFunT<Comm::TcpAcceptor, CommCloseCbParams> Dialer;
    closer_ = JobCallback(5, 4, Dialer, this, Comm::TcpAcceptor::handleClosure);
    comm_add_close_handler(conn->fd, closer_);
}