void
comm_read_base(const Comm::ConnectionPointer &conn, char *buf, int size, AsyncCall::Pointer &callback)
{
    debugs(5, 5, "comm_read, queueing read for " << conn << "; asynCall " << callback);

    /* Make sure we are open and not closing */
    assert(Comm::IsConnOpen(conn));
    assert(!fd_table[conn->fd].closing());
    Comm::IoCallback *ccb = COMMIO_FD_READCB(conn->fd);

    // Make sure we are either not reading or just passively monitoring.
    // Active/passive conflicts are OK and simply cancel passive monitoring.
    if (ccb->active()) {
        // if the assertion below fails, we have an active comm_read conflict
        assert(fd_table[conn->fd].halfClosedReader != NULL);
        commStopHalfClosedMonitor(conn->fd);
        assert(!ccb->active());
    }
    ccb->conn = conn;

    /* Queue the read */
    ccb->setCallback(Comm::IOCB_READ, callback, (char *)buf, NULL, size);
    Comm::SetSelect(conn->fd, COMM_SELECT_READ, Comm::HandleRead, ccb, 0);
}