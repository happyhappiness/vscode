int
comm_openex(int sock_type,
            int proto,
            IpAddress &addr,
            int flags,
            unsigned char TOS,
            const char *note)
{
    int new_socket;
    fde *F = NULL;
    int tos = 0;
    struct addrinfo *AI = NULL;

    PROF_start(comm_open);
    /* Create socket for accepting new connections. */
    statCounter.syscalls.sock.sockets++;

    /* Setup the socket addrinfo details for use */
    addr.GetAddrInfo(AI);
    AI->ai_socktype = sock_type;
    AI->ai_protocol = proto;

    debugs(50, 3, "comm_openex: Attempt open socket for: " << addr );

    new_socket = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);

    /* under IPv6 there is the possibility IPv6 is present but disabled. */
    /* try again as IPv4-native if possible */
    if ( new_socket < 0 && Ip::EnableIpv6 && addr.IsIPv6() && addr.SetIPv4() ) {
        /* attempt to open this IPv4-only. */
        addr.FreeAddrInfo(AI);
        /* Setup the socket addrinfo details for use */
        addr.GetAddrInfo(AI);
        AI->ai_socktype = sock_type;
        AI->ai_protocol = proto;
        debugs(50, 3, "comm_openex: Attempt fallback open socket for: " << addr );
        new_socket = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
        debugs(50, 2, HERE << "attempt open " << note << " socket on: " << addr);
    }

    if (new_socket < 0) {
        /* Increase the number of reserved fd's if calls to socket()
         * are failing because the open file table is full.  This
         * limits the number of simultaneous clients */

        if (limitError(errno)) {
            debugs(50, DBG_IMPORTANT, "comm_open: socket failure: " << xstrerror());
            fdAdjustReserved();
        } else {
            debugs(50, DBG_CRITICAL, "comm_open: socket failure: " << xstrerror());
        }

        addr.FreeAddrInfo(AI);

        PROF_stop(comm_open);
        return -1;
    }

    debugs(50, 3, "comm_openex: Opened socket FD " << new_socket << " : family=" << AI->ai_family << ", type=" << AI->ai_socktype << ", protocol=" << AI->ai_protocol );

    /* set TOS if needed */
    if (TOS && comm_set_tos(new_socket, TOS) ) {
        tos = TOS;
        (void)tos;
    }

    if ( Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && addr.IsIPv6() )
        comm_set_v6only(new_socket, 1);

    /* Windows Vista supports Dual-Sockets. BUT defaults them to V6ONLY. Turn it OFF. */
    /* Other OS may have this administratively disabled for general use. Same deal. */
    if ( Ip::EnableIpv6&IPV6_SPECIAL_V4MAPPING && addr.IsIPv6() )
        comm_set_v6only(new_socket, 0);

    /* update fdstat */
    debugs(5, 5, "comm_open: FD " << new_socket << " is a new socket");

    assert(!isOpen(new_socket));
    fd_open(new_socket, FD_SOCKET, note);

    fdd_table[new_socket].close_file = NULL;

    fdd_table[new_socket].close_line = 0;

    F = &fd_table[new_socket];

    F->local_addr = addr;

    F->tos = TOS;

    F->sock_family = AI->ai_family;

    if (!(flags & COMM_NOCLOEXEC))
        commSetCloseOnExec(new_socket);

    if ((flags & COMM_REUSEADDR))
        commSetReuseAddr(new_socket);

    if (addr.GetPort() > (unsigned short) 0) {
#ifdef _SQUID_MSWIN_
        if (sock_type != SOCK_DGRAM)
#endif
            commSetNoLinger(new_socket);

        if (opt_reuseaddr)
            commSetReuseAddr(new_socket);
    }

    /* MUST be done before binding or face OS Error: "(99) Cannot assign requested address"... */
    if ((flags & COMM_TRANSPARENT)) {
        comm_set_transparent(new_socket);
    }

    if ( (flags & COMM_DOBIND) || addr.GetPort() > 0 || !addr.IsAnyAddr() ) {
        if ( !(flags & COMM_DOBIND) && addr.IsAnyAddr() )
            debugs(5,1,"WARNING: Squid is attempting to bind() port " << addr << " without being a listener.");
        if ( addr.IsNoAddr() )
            debugs(5,0,"CRITICAL: Squid is attempting to bind() port " << addr << "!!");

        if (commBind(new_socket, *AI) != COMM_OK) {
            comm_close(new_socket);
            addr.FreeAddrInfo(AI);
            return -1;
            PROF_stop(comm_open);
        }
    }

    addr.FreeAddrInfo(AI);

    if (flags & COMM_NONBLOCKING)
        if (commSetNonBlocking(new_socket) == COMM_ERROR) {
            return -1;
            PROF_stop(comm_open);
        }

#ifdef TCP_NODELAY
    if (sock_type == SOCK_STREAM)
        commSetTcpNoDelay(new_socket);

#endif

    if (Config.tcpRcvBufsz > 0 && sock_type == SOCK_STREAM)
        commSetTcpRcvbuf(new_socket, Config.tcpRcvBufsz);

    PROF_stop(comm_open);

    return new_socket;
}