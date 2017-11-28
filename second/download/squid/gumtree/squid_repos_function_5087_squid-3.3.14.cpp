comm_err_t
Comm::TcpAcceptor::oldAccept(Comm::ConnectionPointer &details)
{
    PROF_start(comm_accept);
    ++statCounter.syscalls.sock.accepts;
    int sock;
    struct addrinfo *gai = NULL;
    details->local.InitAddrInfo(gai);

    errcode = 0; // reset local errno copy.
    if ((sock = accept(conn->fd, gai->ai_addr, &gai->ai_addrlen)) < 0) {
        errcode = errno; // store last accept errno locally.

        details->local.FreeAddrInfo(gai);

        PROF_stop(comm_accept);

        if (ignoreErrno(errno)) {
            debugs(50, 5, HERE << status() << ": " << xstrerror());
            return COMM_NOMESSAGE;
        } else if (ENFILE == errno || EMFILE == errno) {
            debugs(50, 3, HERE << status() << ": " << xstrerror());
            return COMM_ERROR;
        } else {
            debugs(50, DBG_IMPORTANT, HERE << status() << ": " << xstrerror());
            return COMM_ERROR;
        }
    }

    Must(sock >= 0);
    details->fd = sock;
    details->remote = *gai;

    if ( Config.client_ip_max_connections >= 0) {
        if (clientdbEstablished(details->remote, 0) > Config.client_ip_max_connections) {
            debugs(50, DBG_IMPORTANT, "WARNING: " << details->remote << " attempting more than " << Config.client_ip_max_connections << " connections.");
            details->local.FreeAddrInfo(gai);
            return COMM_ERROR;
        }
    }

    // lookup the local-end details of this new connection
    details->local.InitAddrInfo(gai);
    details->local.SetEmpty();
    getsockname(sock, gai->ai_addr, &gai->ai_addrlen);
    details->local = *gai;
    details->local.FreeAddrInfo(gai);

    /* fdstat update */
    // XXX : these are not all HTTP requests. use a note about type and ip:port details->
    // so we end up with a uniform "(HTTP|FTP-data|HTTPS|...) remote-ip:remote-port"
    fd_open(sock, FD_SOCKET, "HTTP Request");

    fdd_table[sock].close_file = NULL;
    fdd_table[sock].close_line = 0;

    fde *F = &fd_table[sock];
    details->remote.NtoA(F->ipaddr,MAX_IPSTRLEN);
    F->remote_port = details->remote.GetPort();
    F->local_addr = details->local;
    F->sock_family = details->local.IsIPv6()?AF_INET6:AF_INET;

    // set socket flags
    commSetCloseOnExec(sock);
    commSetNonBlocking(sock);

    /* IFF the socket is (tproxy) transparent, pass the flag down to allow spoofing */
    F->flags.transparent = fd_table[conn->fd].flags.transparent; // XXX: can we remove this line yet?

    // Perform NAT or TPROXY operations to retrieve the real client/dest IP addresses
    if (conn->flags&(COMM_TRANSPARENT|COMM_INTERCEPTION) && !Ip::Interceptor.Lookup(details, conn)) {
        // Failed.
        return COMM_ERROR;
    }

    PROF_stop(comm_accept);
    return COMM_OK;
}