static int
comm_old_accept(int fd, ConnectionDetail &details)
{
    PROF_start(comm_accept);
    statCounter.syscalls.sock.accepts++;
    int sock;
    struct addrinfo *gai = NULL;
    details.me.InitAddrInfo(gai);

    if ((sock = accept(fd, gai->ai_addr, &gai->ai_addrlen)) < 0) {

        details.me.FreeAddrInfo(gai);

        PROF_stop(comm_accept);

        if (ignoreErrno(errno)) {
            debugs(50, 5, "comm_old_accept: FD " << fd << ": " << xstrerror());
            return COMM_NOMESSAGE;
        } else if (ENFILE == errno || EMFILE == errno) {
            debugs(50, 3, "comm_old_accept: FD " << fd << ": " << xstrerror());
            return COMM_ERROR;
        } else {
            debugs(50, 1, "comm_old_accept: FD " << fd << ": " << xstrerror());
            return COMM_ERROR;
        }
    }

    details.peer = *gai;

    if ( Config.client_ip_max_connections >= 0) {
        if (clientdbEstablished(details.peer, 0) > Config.client_ip_max_connections) {
            debugs(50, DBG_IMPORTANT, "WARNING: " << details.peer << " attempting more than " << Config.client_ip_max_connections << " connections.");
            details.me.FreeAddrInfo(gai);
            return COMM_ERROR;
        }
    }

    details.me.InitAddrInfo(gai);

    details.me.SetEmpty();
    getsockname(sock, gai->ai_addr, &gai->ai_addrlen);
    details.me = *gai;

    commSetCloseOnExec(sock);

    /* fdstat update */
    fd_open(sock, FD_SOCKET, "HTTP Request");
    fdd_table[sock].close_file = NULL;
    fdd_table[sock].close_line = 0;
    fde *F = &fd_table[sock];
    details.peer.NtoA(F->ipaddr,MAX_IPSTRLEN);
    F->remote_port = details.peer.GetPort();
    F->local_addr.SetPort(details.me.GetPort());
    F->sock_family = details.me.IsIPv6()?AF_INET6:AF_INET;
    details.me.FreeAddrInfo(gai);

    commSetNonBlocking(sock);

    /* IFF the socket is (tproxy) transparent, pass the flag down to allow spoofing */
    F->flags.transparent = fd_table[fd].flags.transparent;

    PROF_stop(comm_accept);
    return sock;
}