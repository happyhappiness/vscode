static int
comm_apply_flags(int new_socket,
                 Ip::Address &addr,
                 int flags,
                 struct addrinfo *AI)
{
    assert(new_socket >= 0);
    assert(AI);
    const int sock_type = AI->ai_socktype;

    if (!(flags & COMM_NOCLOEXEC))
        commSetCloseOnExec(new_socket);

    if ((flags & COMM_REUSEADDR))
        commSetReuseAddr(new_socket);

    if (addr.GetPort() > (unsigned short) 0) {
#if _SQUID_WINDOWS_
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
            debugs(5, DBG_IMPORTANT,"WARNING: Squid is attempting to bind() port " << addr << " without being a listener.");
        if ( addr.IsNoAddr() )
            debugs(5,0,"CRITICAL: Squid is attempting to bind() port " << addr << "!!");

        if (commBind(new_socket, *AI) != COMM_OK) {
            comm_close(new_socket);
            return -1;
        }
    }

    if (flags & COMM_NONBLOCKING)
        if (commSetNonBlocking(new_socket) == COMM_ERROR) {
            comm_close(new_socket);
            return -1;
        }

#ifdef TCP_NODELAY
    if (sock_type == SOCK_STREAM)
        commSetTcpNoDelay(new_socket);

#endif

    if (Config.tcpRcvBufsz > 0 && sock_type == SOCK_STREAM)
        commSetTcpRcvbuf(new_socket, Config.tcpRcvBufsz);

    return new_socket;
}