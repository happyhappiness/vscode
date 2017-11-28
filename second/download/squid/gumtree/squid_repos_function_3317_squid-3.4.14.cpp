void
IdleConnList::clearHandlers(const Comm::ConnectionPointer &conn)
{
    debugs(48, 3, HERE << "removing close handler for " << conn);
    comm_read_cancel(conn->fd, IdleConnList::Read, this);
    commUnsetConnTimeout(conn);
}