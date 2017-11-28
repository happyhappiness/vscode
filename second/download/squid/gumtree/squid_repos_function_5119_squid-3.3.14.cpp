void
Comm::Write(const Comm::ConnectionPointer &conn, const char *buf, int size, AsyncCall::Pointer &callback, FREE * free_func)
{
    debugs(5, 5, HERE << conn << ": sz " << size << ": asynCall " << callback);

    /* Make sure we are open, not closing, and not writing */
    assert(fd_table[conn->fd].flags.open);
    assert(!fd_table[conn->fd].closing());
    Comm::IoCallback *ccb = COMMIO_FD_WRITECB(conn->fd);
    assert(!ccb->active());

    fd_table[conn->fd].writeStart = squid_curtime;
    ccb->conn = conn;
    /* Queue the write */
    ccb->setCallback(IOCB_WRITE, callback, (char *)buf, free_func, size);
    ccb->selectOrQueueWrite();
}