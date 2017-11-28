void
comm_init_opened(const Comm::ConnectionPointer &conn,
                 tos_t tos,
                 nfmark_t nfmark,
                 const char *note,
                 struct addrinfo *AI)
{
    assert(Comm::IsConnOpen(conn));
    assert(AI);

    /* update fdstat */
    debugs(5, 5, HERE << conn << " is a new socket");

    assert(!isOpen(conn->fd)); // NP: global isOpen checks the fde entry for openness not the Comm::Connection
    fd_open(conn->fd, FD_SOCKET, note);

    fdd_table[conn->fd].close_file = NULL;
    fdd_table[conn->fd].close_line = 0;

    fde *F = &fd_table[conn->fd];
    F->local_addr = conn->local;
    F->tosToServer = tos;

    F->nfmarkToServer = nfmark;

    F->sock_family = AI->ai_family;
}