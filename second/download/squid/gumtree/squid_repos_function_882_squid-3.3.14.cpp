int
comm_connect_addr(int sock, const Ip::Address &address)
{
    comm_err_t status = COMM_OK;
    fde *F = &fd_table[sock];
    int x = 0;
    int err = 0;
    socklen_t errlen;
    struct addrinfo *AI = NULL;
    PROF_start(comm_connect_addr);

    assert(address.GetPort() != 0);

    debugs(5, 9, HERE << "connecting socket FD " << sock << " to " << address << " (want family: " << F->sock_family << ")");

    /* Handle IPv6 over IPv4-only socket case.
     * this case must presently be handled here since the GetAddrInfo asserts on bad mappings.
     * NP: because commResetFD is private to ConnStateData we have to return an error and
     *     trust its handled properly.
     */
    if (F->sock_family == AF_INET && !address.IsIPv4()) {
        errno = ENETUNREACH;
        return COMM_ERR_PROTOCOL;
    }

    /* Handle IPv4 over IPv6-only socket case.
     * This case is presently handled here as it's both a known case and it's
     * uncertain what error will be returned by the IPv6 stack in such case. It's
     * possible this will also be handled by the errno checks below after connect()
     * but needs carefull cross-platform verification, and verifying the address
     * condition here is simple.
     */
    if (!F->local_addr.IsIPv4() && address.IsIPv4()) {
        errno = ENETUNREACH;
        return COMM_ERR_PROTOCOL;
    }

    address.GetAddrInfo(AI, F->sock_family);

    /* Establish connection. */
    errno = 0;

    if (!F->flags.called_connect) {
        F->flags.called_connect = 1;
        ++ statCounter.syscalls.sock.connects;

        x = connect(sock, AI->ai_addr, AI->ai_addrlen);

        // XXX: ICAP code refuses callbacks during a pending comm_ call
        // Async calls development will fix this.
        if (x == 0) {
            x = -1;
            errno = EINPROGRESS;
        }

        if (x < 0) {
            debugs(5,5, "comm_connect_addr: sock=" << sock << ", addrinfo( " <<
                   " flags=" << AI->ai_flags <<
                   ", family=" << AI->ai_family <<
                   ", socktype=" << AI->ai_socktype <<
                   ", protocol=" << AI->ai_protocol <<
                   ", &addr=" << AI->ai_addr <<
                   ", addrlen=" << AI->ai_addrlen <<
                   " )" );
            debugs(5, 9, "connect FD " << sock << ": (" << x << ") " << xstrerror());
            debugs(14,9, "connecting to: " << address );
        }
    } else {
#if _SQUID_NEWSOS6_
        /* Makoto MATSUSHITA <matusita@ics.es.osaka-u.ac.jp> */

        connect(sock, AI->ai_addr, AI->ai_addrlen);

        if (errno == EINVAL) {
            errlen = sizeof(err);
            x = getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &errlen);

            if (x >= 0)
                errno = x;
        }

#else
        errlen = sizeof(err);

        x = getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &errlen);

        if (x == 0)
            errno = err;

#if _SQUID_SOLARIS_
        /*
        * Solaris 2.4's socket emulation doesn't allow you
        * to determine the error from a failed non-blocking
        * connect and just returns EPIPE.  Create a fake
        * error message for connect.   -- fenner@parc.xerox.com
        */
        if (x < 0 && errno == EPIPE)
            errno = ENOTCONN;

#endif
#endif

    }

    /* Squid seems to be working fine without this code. With this code,
     * we leak memory on many connect requests because of EINPROGRESS.
     * If you find that this code is needed, please file a bug report. */
#if 0
#if _SQUID_LINUX_
    /* 2007-11-27:
     * Linux Debian replaces our allocated AI pointer with garbage when
     * connect() fails. This leads to segmentation faults deallocating
     * the system-allocated memory when we go to clean up our pointer.
     * HACK: is to leak the memory returned since we can't deallocate.
     */
    if (errno != 0) {
        AI = NULL;
    }
#endif
#endif

    address.FreeAddrInfo(AI);

    PROF_stop(comm_connect_addr);

    if (errno == 0 || errno == EISCONN)
        status = COMM_OK;
    else if (ignoreErrno(errno))
        status = COMM_INPROGRESS;
    else if (errno == EAFNOSUPPORT || errno == EINVAL)
        return COMM_ERR_PROTOCOL;
    else
        return COMM_ERROR;

    address.NtoA(F->ipaddr, MAX_IPSTRLEN);

    F->remote_port = address.GetPort(); /* remote_port is HS */

    if (status == COMM_OK) {
        debugs(5, DBG_DATA, "comm_connect_addr: FD " << sock << " connected to " << address);
    } else if (status == COMM_INPROGRESS) {
        debugs(5, DBG_DATA, "comm_connect_addr: FD " << sock << " connection pending");
    }

    return status;
}