void
commHandleRead(int fd, void *data)
{
    comm_io_callback_t *ccb = (comm_io_callback_t *) data;

    assert(data == COMMIO_FD_READCB(fd));
    assert(commio_has_callback(fd, IOCB_READ, ccb));
    /* Attempt a read */
    statCounter.syscalls.sock.reads++;
    errno = 0;
    int retval;
    retval = FD_READ_METHOD(fd, ccb->buf, ccb->size);
    debugs(5, 3, "comm_read_try: FD " << fd << ", size " << ccb->size << ", retval " << retval << ", errno " << errno);

    if (retval < 0 && !ignoreErrno(errno)) {
        debugs(5, 3, "comm_read_try: scheduling COMM_ERROR");
        ccb->offset = 0;
        commio_finish_callback(fd, ccb, COMM_ERROR, errno);
        return;
    };

    /* See if we read anything */
    /* Note - read 0 == socket EOF, which is a valid read */
    if (retval >= 0) {
        fd_bytes(fd, retval, FD_READ);
        ccb->offset = retval;
        commio_finish_callback(fd, ccb, COMM_OK, errno);
        return;
    }

    /* Nope, register for some more IO */
    commSetSelect(fd, COMM_SELECT_READ, commHandleRead, data, 0);
}