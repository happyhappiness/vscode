void
comm_read(int fd, char *buf, int size, AsyncCall::Pointer &callback)
{
    debugs(5, 5, "comm_read, queueing read for FD " << fd << "; asynCall " << callback);

    /* Make sure we are open and not closing */
    assert(isOpen(fd));
    assert(!fd_table[fd].closing());
    comm_io_callback_t *ccb = COMMIO_FD_READCB(fd);

    // Make sure we are either not reading or just passively monitoring.
    // Active/passive conflicts are OK and simply cancel passive monitoring.
    if (ccb->active()) {
        // if the assertion below fails, we have an active comm_read conflict
        assert(fd_table[fd].halfClosedReader != NULL);
        commStopHalfClosedMonitor(fd);
        assert(!ccb->active());
    }

    /* Queue the read */
    commio_set_callback(fd, IOCB_READ, ccb, callback, (char *)buf, NULL, size);
    commSetSelect(fd, COMM_SELECT_READ, commHandleRead, ccb, 0);
}