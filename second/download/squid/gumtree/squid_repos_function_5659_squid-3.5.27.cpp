Comm::Flag
Comm::TcpAcceptor::oldAccept(Comm::ConnectionPointer &details)
{
    PROF_start(comm_accept);
    ++statCounter.syscalls.sock.accepts;
    int sock;
    struct addrinfo *gai = NULL;
    Ip::Address::InitAddr(gai);

    errcode = 0; // reset local errno copy.
    if ((sock = accept(conn->fd, gai->ai_addr, &gai->ai_addrlen)) < 0) {
        errcode = errno; // store last accept errno locally.

        Ip::Address::FreeAddr(gai);

        PROF_stop(comm_accept);

        if (ignoreErrno(errno)) {
            debugs(50, 5, HERE << status() << ": " << xstrerror());
            return Comm::NOMESSAGE;
        } else if (ENFILE == errno || EMFILE == errno) {
            debugs(50, 3, HERE << status() << ": " << xstrerror());
            return Comm::COMM_ERROR;
        } else {
            debugs(50, DBG_IMPORTANT, HERE << status() << ": " << xstrerror());
            return Comm::COMM_ERROR;
        }
    }

    Must(sock >= 0);
    details->fd = sock;
    details->remote = *gai;

    if ( Config.client_ip_max_connections >= 0) {
        if (clientdbEstablished(details->remote, 0) > Config.client_ip_max_connections) {
            debugs(50, DBG_IMPORTANT, "WARNING: " << details->remote << " attempting more than " << Config.client_ip_max_connections << " connections.");
            Ip::Address::FreeAddr(gai);
            PROF_stop(comm_accept);
            return Comm::COMM_ERROR;
        }
    }

    // lookup the local-end details of this new connection
    Ip::Address::InitAddr(gai);
    details->local.setEmpty();
    if (getsockname(sock, gai->ai_addr, &gai->ai_addrlen) != 0) {
        debugs(50, DBG_IMPORTANT, "ERROR: getsockname() failed to locate local-IP on " << details << ": " << xstrerror());
        Ip::Address::FreeAddr(gai);
        PROF_stop(comm_accept);
        return Comm::COMM_ERROR;
    }
    details->local = *gai;
    Ip::Address::FreeAddr(gai);

    /* fdstat update */
    // XXX : these are not all HTTP requests. use a note about type and ip:port details->
    // so we end up with a uniform "(HTTP|FTP-data|HTTPS|...) remote-ip:remote-port"
    fd_open(sock, FD_SOCKET, "HTTP Request");

    fdd_table[sock].close_file = NULL;
    fdd_table[sock].close_line = 0;

    fde *F = &fd_table[sock];
    details->remote.toStr(F->ipaddr,MAX_IPSTRLEN);
    F->remote_port = details->remote.port();
    F->local_addr = details->local;
    F->sock_family = details->local.isIPv6()?AF_INET6:AF_INET;

    // set socket flags
    commSetCloseOnExec(sock);
    commSetNonBlocking(sock);

    /* IFF the socket is (tproxy) transparent, pass the flag down to allow spoofing */
    F->flags.transparent = fd_table[conn->fd].flags.transparent; // XXX: can we remove this line yet?

    // Perform NAT or TPROXY operations to retrieve the real client/dest IP addresses
    if (conn->flags&(COMM_TRANSPARENT|COMM_INTERCEPTION) && !Ip::Interceptor.Lookup(details, conn)) {
        debugs(50, DBG_IMPORTANT, "ERROR: NAT/TPROXY lookup failed to locate original IPs on " << details);
        // Failed.
        PROF_stop(comm_accept);
        return Comm::COMM_ERROR;
    }

#if USE_SQUID_EUI
    if (Eui::TheConfig.euiLookup) {
        if (details->remote.isIPv4()) {
            details->remoteEui48.lookup(details->remote);
        } else if (details->remote.isIPv6()) {
            details->remoteEui64.lookup(details->remote);
        }
    }
#endif

    PROF_stop(comm_accept);
    return Comm::OK;
}