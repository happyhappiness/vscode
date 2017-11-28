void
FwdState::unregister(Comm::ConnectionPointer &conn)
{
    debugs(17, 3, HERE << entry->url() );
    assert(serverConnection() == conn);
    assert(Comm::IsConnOpen(conn));
    comm_remove_close_handler(conn->fd, closeHandler);
    closeHandler = NULL;
    serverConn = NULL;
}