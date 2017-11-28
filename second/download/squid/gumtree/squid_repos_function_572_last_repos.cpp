int
comm_openex(int sock_type,
            int proto,
            Ip::Address &addr,
            int flags,
            const char *note)
{
    int new_socket;
    struct addrinfo *AI = NULL;

    PROF_start(comm_open);
    /* Create socket for accepting new connections. */
    ++ statCounter.syscalls.sock.sockets;

    /* Setup the socket addrinfo details for use */
    addr.getAddrInfo(AI);
    AI->ai_socktype = sock_type;
    AI->ai_protocol = proto;

    debugs(50, 3, "comm_openex: Attempt open socket for: " << addr );

    new_socket = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
    int xerrno = errno;

    /* under IPv6 there is the possibility IPv6 is present but disabled. */
    /* try again as IPv4-native if possible */
    if ( new_socket < 0 && Ip::EnableIpv6 && addr.isIPv6() && addr.setIPv4() ) {
        /* attempt to open this IPv4-only. */
        Ip::Address::FreeAddr(AI);
        /* Setup the socket addrinfo details for use */
        addr.getAddrInfo(AI);
        AI->ai_socktype = sock_type;
        AI->ai_protocol = proto;
        debugs(50, 3, "Attempt fallback open socket for: " << addr );
        new_socket = socket(AI->ai_family, AI->ai_socktype, AI->ai_protocol);
        debugs(50, 2, "attempt open " << note << " socket on: " << addr);
    }

    if (new_socket < 0) {
        /* Increase the number of reserved fd's if calls to socket()
         * are failing because the open file table is full.  This
         * limits the number of simultaneous clients */

        if (limitError(errno)) {
            debugs(50, DBG_IMPORTANT, MYNAME << "socket failure: " << xstrerr(xerrno));
            fdAdjustReserved();
        } else {
            debugs(50, DBG_CRITICAL, MYNAME << "socket failure: " << xstrerr(xerrno));
        }

        Ip::Address::FreeAddr(AI);

        PROF_stop(comm_open);
        errno = xerrno; // restore for caller
        return -1;
    }

    // XXX: temporary for the transition. comm_openex will eventually have a conn to play with.
    Comm::ConnectionPointer conn = new Comm::Connection;
    conn->local = addr;
    conn->fd = new_socket;

    debugs(50, 3, "comm_openex: Opened socket " << conn << " : family=" << AI->ai_family << ", type=" << AI->ai_socktype << ", protocol=" << AI->ai_protocol );

    if ( Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && addr.isIPv6() )
        comm_set_v6only(conn->fd, 1);

    /* Windows Vista supports Dual-Sockets. BUT defaults them to V6ONLY. Turn it OFF. */
    /* Other OS may have this administratively disabled for general use. Same deal. */
    if ( Ip::EnableIpv6&IPV6_SPECIAL_V4MAPPING && addr.isIPv6() )
        comm_set_v6only(conn->fd, 0);

    comm_init_opened(conn, note, AI);
    new_socket = comm_apply_flags(conn->fd, addr, flags, AI);

    Ip::Address::FreeAddr(AI);

    PROF_stop(comm_open);

    // XXX transition only. prevent conn from closing the new FD on function exit.
    conn->fd = -1;
    errno = xerrno; // restore for caller
    return new_socket;
}