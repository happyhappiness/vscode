void
Ftp::Channel::opened(const Comm::ConnectionPointer &newConn,
                     const AsyncCall::Pointer &aCloser)
{
    assert(!Comm::IsConnOpen(conn));
    assert(closer == NULL);

    assert(Comm::IsConnOpen(newConn));
    assert(aCloser != NULL);

    conn = newConn;
    closer = aCloser;
    comm_add_close_handler(conn->fd, closer);
}