void
comm_write(int fd, const char *buf, int size, AsyncCall::Pointer &callback, FREE * free_func)
{
    debugs(5, 5, "comm_write: FD " << fd << ": sz " << size << ": asynCall " << callback);

    /* Make sure we are open, not closing, and not writing */
    assert(isOpen(fd));
    assert(!fd_table[fd].closing());
    comm_io_callback_t *ccb = COMMIO_FD_WRITECB(fd);
    assert(!ccb->active());

    /* Queue the write */
    commio_set_callback(fd, IOCB_WRITE, ccb, callback,
                        (char *)buf, free_func, size);
    commSetSelect(fd, COMM_SELECT_WRITE, commHandleWrite, ccb, 0);
}