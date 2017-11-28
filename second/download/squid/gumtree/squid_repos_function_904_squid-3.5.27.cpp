void
comm_import_opened(const Comm::ConnectionPointer &conn,
                   const char *note,
                   struct addrinfo *AI)
{
    debugs(5, 2, HERE << conn);
    assert(Comm::IsConnOpen(conn));
    assert(AI);

    comm_init_opened(conn, note, AI);

    if (!(conn->flags & COMM_NOCLOEXEC))
        fd_table[conn->fd].flags.close_on_exec = true;

    if (conn->local.port() > (unsigned short) 0) {
#if _SQUID_WINDOWS_
        if (AI->ai_socktype != SOCK_DGRAM)
#endif
            fd_table[conn->fd].flags.nolinger = true;
    }

    if ((conn->flags & COMM_TRANSPARENT))
        fd_table[conn->fd].flags.transparent = true;

    if (conn->flags & COMM_NONBLOCKING)
        fd_table[conn->fd].flags.nonblocking = true;

#ifdef TCP_NODELAY
    if (AI->ai_socktype == SOCK_STREAM)
        fd_table[conn->fd].flags.nodelay = true;
#endif

    /* no fd_table[fd].flags. updates needed for these conditions:
     * if ((flags & COMM_REUSEADDR)) ...
     * if ((flags & COMM_DOBIND) ...) ...
     */
}