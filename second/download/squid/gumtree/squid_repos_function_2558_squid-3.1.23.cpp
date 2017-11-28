static int
ftpOpenListenSocket(FtpStateData * ftpState, int fallback)
{
    int fd;

    IpAddress addr;
    struct addrinfo *AI = NULL;
    int on = 1;
    int x = 0;

    /// Close old data channel, if any. We may open a new one below.
    ftpState->data.close();
    safe_free(ftpState->data.host);

    /*
     * Set up a listen socket on the same local address as the
     * control connection.
     */

    addr.InitAddrInfo(AI);

    x = getsockname(ftpState->ctrl.fd, AI->ai_addr, &AI->ai_addrlen);

    addr = *AI;

    addr.FreeAddrInfo(AI);

    if (x) {
        debugs(9, DBG_CRITICAL, HERE << "getsockname(" << ftpState->ctrl.fd << ",..): " << xstrerror());
        return -1;
    }

    /*
     * REUSEADDR is needed in fallback mode, since the same port is
     * used for both control and data.
     */
    if (fallback) {
        setsockopt(ftpState->ctrl.fd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    } else {
        /* if not running in fallback mode a new port needs to be retrieved */
        addr.SetPort(0);
    }

    fd = comm_open(SOCK_STREAM,
                   IPPROTO_TCP,
                   addr,
                   COMM_NONBLOCKING | (fallback ? COMM_REUSEADDR : 0),
                   ftpState->entry->url());
    debugs(9, 3, HERE << "Unconnected data socket created on FD " << fd  );

    if (fd < 0) {
        debugs(9, DBG_CRITICAL, HERE << "comm_open failed");
        return -1;
    }

    if (comm_listen(fd) < 0) {
        comm_close(fd);
        return -1;
    }

    ftpState->data.opened(fd, ftpState->dataCloser());
    ftpState->data.port = comm_local_port(fd);
    ftpState->data.host = NULL;
    return fd;
}