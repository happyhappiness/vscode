pid_t
ipcCreate(int type, const char *prog, const char *const args[], const char *name, IpAddress &local_addr, int *rfd, int *wfd, void **hIpc)
{
    pid_t pid;
    IpAddress ChS;
    IpAddress PaS;
    struct addrinfo *AI = NULL;
    int crfd = -1;
    int prfd = -1;
    int cwfd = -1;
    int pwfd = -1;
    int fd;
    int t1, t2, t3;
    int x;

#if USE_POLL && defined(_SQUID_OSF_)

    assert(type != IPC_FIFO);
#endif

    if (rfd)
        *rfd = -1;

    if (wfd)
        *wfd = -1;

    if (hIpc)
        *hIpc = NULL;

    if (type == IPC_TCP_SOCKET) {
        crfd = cwfd = comm_open(SOCK_STREAM,
                                0,
                                local_addr,
                                COMM_NOCLOEXEC,
                                name);
        prfd = pwfd = comm_open(SOCK_STREAM,
                                0,			/* protocol */
                                local_addr,
                                0,			/* blocking */
                                name);
    } else if (type == IPC_UDP_SOCKET) {
        crfd = cwfd = comm_open(SOCK_DGRAM,
                                0,
                                local_addr,
                                COMM_NOCLOEXEC,
                                name);
        prfd = pwfd = comm_open(SOCK_DGRAM,
                                0,
                                local_addr,
                                0,
                                name);
    } else if (type == IPC_FIFO) {
        int p2c[2];
        int c2p[2];

        if (pipe(p2c) < 0) {
            debugs(54, 0, "ipcCreate: pipe: " << xstrerror());
            return -1;
        }

        if (pipe(c2p) < 0) {
            debugs(54, 0, "ipcCreate: pipe: " << xstrerror());
            return -1;
        }

        fd_open(prfd = p2c[0], FD_PIPE, "IPC FIFO Parent Read");
        fd_open(cwfd = p2c[1], FD_PIPE, "IPC FIFO Child Write");
        fd_open(crfd = c2p[0], FD_PIPE, "IPC FIFO Child Read");
        fd_open(pwfd = c2p[1], FD_PIPE, "IPC FIFO Parent Write");
#if HAVE_SOCKETPAIR && defined(AF_UNIX)

    } else if (type == IPC_UNIX_STREAM) {
        int fds[2];
        int buflen = 32768;

        if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) < 0) {
            debugs(54, 0, "ipcCreate: socketpair: " << xstrerror());
            return -1;
        }

        setsockopt(fds[0], SOL_SOCKET, SO_SNDBUF, (void *) &buflen, sizeof(buflen));
        setsockopt(fds[0], SOL_SOCKET, SO_RCVBUF, (void *) &buflen, sizeof(buflen));
        setsockopt(fds[1], SOL_SOCKET, SO_SNDBUF, (void *) &buflen, sizeof(buflen));
        setsockopt(fds[1], SOL_SOCKET, SO_RCVBUF, (void *) &buflen, sizeof(buflen));
        fd_open(prfd = pwfd = fds[0], FD_PIPE, "IPC UNIX STREAM Parent");
        fd_open(crfd = cwfd = fds[1], FD_PIPE, "IPC UNIX STREAM Parent");
    } else if (type == IPC_UNIX_DGRAM) {
        int fds[2];

        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fds) < 0) {
            debugs(54, 0, "ipcCreate: socketpair: " << xstrerror());
            return -1;
        }

        fd_open(prfd = pwfd = fds[0], FD_PIPE, "IPC UNIX DGRAM Parent");
        fd_open(crfd = cwfd = fds[1], FD_PIPE, "IPC UNIX DGRAM Parent");
#endif

    } else {
        assert(IPC_NONE);
    }

    debugs(54, 3, "ipcCreate: prfd FD " << prfd);
    debugs(54, 3, "ipcCreate: pwfd FD " << pwfd);
    debugs(54, 3, "ipcCreate: crfd FD " << crfd);
    debugs(54, 3, "ipcCreate: cwfd FD " << cwfd);

    if (crfd < 0) {
        debugs(54, 0, "ipcCreate: Failed to create child FD.");
        return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
    }

    if (pwfd < 0) {
        debugs(54, 0, "ipcCreate: Failed to create server FD.");
        return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
    }

    if (type == IPC_TCP_SOCKET || type == IPC_UDP_SOCKET) {
        PaS.InitAddrInfo(AI);

        if (getsockname(pwfd, AI->ai_addr, &AI->ai_addrlen) < 0) {
            PaS.FreeAddrInfo(AI);
            debugs(54, 0, "ipcCreate: getsockname: " << xstrerror());
            return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
        }

        PaS = *AI;

        debugs(54, 3, "ipcCreate: FD " << pwfd << " sockaddr " << PaS);

        PaS.FreeAddrInfo(AI);

        ChS.InitAddrInfo(AI);

        if (getsockname(crfd, AI->ai_addr, &AI->ai_addrlen) < 0) {
            ChS.FreeAddrInfo(AI);
            debugs(54, 0, "ipcCreate: getsockname: " << xstrerror());
            return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
        }

        ChS = *AI;

        ChS.FreeAddrInfo(AI);

        debugs(54, 3, "ipcCreate: FD " << crfd << " sockaddr " << ChS );

    }

    if (type == IPC_TCP_SOCKET) {
        if (listen(crfd, 1) < 0) {
            debugs(54, 1, "ipcCreate: listen FD " << crfd << ": " << xstrerror());
            return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
        }

        debugs(54, 3, "ipcCreate: FD " << crfd << " listening...");
    }

    /* flush or else we get dup data if unbuffered_logs is set */
    logsFlush();

    if ((pid = fork()) < 0) {
        debugs(54, 1, "ipcCreate: fork: " << xstrerror());
        return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
    }

    if (pid > 0) {		/* parent */
        /* close shared socket with child */
        comm_close(crfd);

        if (cwfd != crfd)
            comm_close(cwfd);

        cwfd = crfd = -1;

        if (type == IPC_TCP_SOCKET || type == IPC_UDP_SOCKET) {
            if (comm_connect_addr(pwfd, ChS) == COMM_ERROR)
                return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
        }

        memset(hello_buf, '\0', HELLO_BUF_SZ);

        if (type == IPC_UDP_SOCKET)
            x = comm_udp_recv(prfd, hello_buf, HELLO_BUF_SZ - 1, 0);
        else
            x = read(prfd, hello_buf, HELLO_BUF_SZ - 1);

        if (x < 0) {
            debugs(54, 0, "ipcCreate: PARENT: hello read test failed");
            debugs(54, 0, "--> read: " << xstrerror());
            return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
        } else if (strcmp(hello_buf, hello_string)) {
            debugs(54, 0, "ipcCreate: PARENT: hello read test failed");
            debugs(54, 0, "--> read returned " << x);
            debugs(54, 0, "--> got '" << rfc1738_escape(hello_buf) << "'");
            return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
        }

        commSetTimeout(prfd, -1, NULL, NULL);
        commSetNonBlocking(prfd);
        commSetNonBlocking(pwfd);

        if (rfd)
            *rfd = prfd;

        if (wfd)
            *wfd = pwfd;

        fd_table[prfd].flags.ipc = 1;

        fd_table[pwfd].flags.ipc = 1;

        if (Config.sleep_after_fork) {
            /* XXX emulation of usleep() */

            struct timeval sl;
            sl.tv_sec = Config.sleep_after_fork / 1000000;
            sl.tv_usec = Config.sleep_after_fork % 1000000;
            select(0, NULL, NULL, NULL, &sl);
        }

        return pid;
    }

    /* child */
    no_suid();			/* give up extra priviliges */

    /* close shared socket with parent */
    close(prfd);

    if (pwfd != prfd)
        close(pwfd);

    pwfd = prfd = -1;

    if (type == IPC_TCP_SOCKET) {
        debugs(54, 3, "ipcCreate: calling accept on FD " << crfd);

        if ((fd = accept(crfd, NULL, NULL)) < 0) {
            debugs(54, 0, "ipcCreate: FD " << crfd << " accept: " << xstrerror());
            _exit(1);
        }

        debugs(54, 3, "ipcCreate: CHILD accepted new FD " << fd);
        close(crfd);
        cwfd = crfd = fd;
    } else if (type == IPC_UDP_SOCKET) {
        if (comm_connect_addr(crfd, PaS) == COMM_ERROR)
            return ipcCloseAllFD(prfd, pwfd, crfd, cwfd);
    }

    if (type == IPC_UDP_SOCKET) {
        x = comm_udp_send(cwfd, hello_string, strlen(hello_string) + 1, 0);

        if (x < 0) {
            debugs(54, 0, "sendto FD " << cwfd << ": " << xstrerror());
            debugs(54, 0, "ipcCreate: CHILD: hello write test failed");
            _exit(1);
        }
    } else {
        if (write(cwfd, hello_string, strlen(hello_string) + 1) < 0) {
            debugs(54, 0, "write FD " << cwfd << ": " << xstrerror());
            debugs(54, 0, "ipcCreate: CHILD: hello write test failed");
            _exit(1);
        }
    }

    PutEnvironment();
    /*
     * This double-dup stuff avoids problems when one of
     *  crfd, cwfd, or debug_log are in the rage 0-2.
     */

    do {
        /* First make sure 0-2 is occupied by something. Gets cleaned up later */
        x = dup(crfd);
        assert(x > -1);
    } while (x < 3 && x > -1);

    close(x);

    t1 = dup(crfd);

    t2 = dup(cwfd);

    t3 = dup(fileno(debug_log));

    assert(t1 > 2 && t2 > 2 && t3 > 2);

    close(crfd);

    close(cwfd);

    close(fileno(debug_log));

    dup2(t1, 0);

    dup2(t2, 1);

    dup2(t3, 2);

    close(t1);

    close(t2);

    close(t3);

    /* Make sure all other filedescriptors are closed */
    for (x = 3; x < SQUID_MAXFD; x++)
        close(x);

#if HAVE_SETSID
    if (opt_no_daemon)
        setsid();
#endif

    execvp(prog, (char *const *) args);

    debug_log = fdopen(2, "a+");

    debugs(54, 0, "ipcCreate: " << prog << ": " << xstrerror());

    _exit(1);

    return 0;
}