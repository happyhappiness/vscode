int
comm_open_uds(int sock_type,
              int proto,
              struct sockaddr_un* addr,
              int flags)
{
    // TODO: merge with comm_openex() when Ip::Address becomes NetAddress

    int new_socket;

    PROF_start(comm_open);
    /* Create socket for accepting new connections. */
    ++ statCounter.syscalls.sock.sockets;

    /* Setup the socket addrinfo details for use */
    struct addrinfo AI;
    AI.ai_flags = 0;
    AI.ai_family = PF_UNIX;
    AI.ai_socktype = sock_type;
    AI.ai_protocol = proto;
    AI.ai_addrlen = SUN_LEN(addr);
    AI.ai_addr = (sockaddr*)addr;
    AI.ai_canonname = NULL;
    AI.ai_next = NULL;

    debugs(50, 3, HERE << "Attempt open socket for: " << addr->sun_path);

    if ((new_socket = socket(AI.ai_family, AI.ai_socktype, AI.ai_protocol)) < 0) {
        /* Increase the number of reserved fd's if calls to socket()
         * are failing because the open file table is full.  This
         * limits the number of simultaneous clients */

        if (limitError(errno)) {
            debugs(50, DBG_IMPORTANT, HERE << "socket failure: " << xstrerror());
            fdAdjustReserved();
        } else {
            debugs(50, DBG_CRITICAL, HERE << "socket failure: " << xstrerror());
        }

        PROF_stop(comm_open);
        return -1;
    }

    debugs(50, 3, "Opened UDS FD " << new_socket << " : family=" << AI.ai_family << ", type=" << AI.ai_socktype << ", protocol=" << AI.ai_protocol);

    /* update fdstat */
    debugs(50, 5, HERE << "FD " << new_socket << " is a new socket");

    assert(!isOpen(new_socket));
    fd_open(new_socket, FD_MSGHDR, NULL);

    fdd_table[new_socket].close_file = NULL;

    fdd_table[new_socket].close_line = 0;

    fd_table[new_socket].sock_family = AI.ai_family;

    if (!(flags & COMM_NOCLOEXEC))
        commSetCloseOnExec(new_socket);

    if (flags & COMM_REUSEADDR)
        commSetReuseAddr(new_socket);

    if (flags & COMM_NONBLOCKING) {
        if (commSetNonBlocking(new_socket) != COMM_OK) {
            comm_close(new_socket);
            PROF_stop(comm_open);
            return -1;
        }
    }

    if (flags & COMM_DOBIND) {
        if (commBind(new_socket, AI) != COMM_OK) {
            comm_close(new_socket);
            PROF_stop(comm_open);
            return -1;
        }
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