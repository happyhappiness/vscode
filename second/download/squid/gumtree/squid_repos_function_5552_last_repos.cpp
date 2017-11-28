void
Comm::HandleRead(int fd, void *data)
{
    Comm::IoCallback *ccb = (Comm::IoCallback *) data;

    assert(data == COMMIO_FD_READCB(fd));
    assert(ccb->active());

    // Without a buffer, just call back.
    // The callee may ReadMore() to get the data.
    if (!ccb->buf) {
        ccb->finish(Comm::OK, 0);
        return;
    }

    /* For legacy callers : Attempt a read */
    // Keep in sync with Comm::ReadNow()!
    ++ statCounter.syscalls.sock.reads;
    int xerrno = errno = 0;
    int retval = FD_READ_METHOD(fd, ccb->buf, ccb->size);
    xerrno = errno;
    debugs(5, 3, "FD " << fd << ", size " << ccb->size << ", retval " << retval << ", errno " << xerrno);

    /* See if we read anything */
    /* Note - read 0 == socket EOF, which is a valid read */
    if (retval >= 0) {
        fd_bytes(fd, retval, FD_READ);
        ccb->offset = retval;
        ccb->finish(Comm::OK, 0);
        return;
    } else if (retval < 0 && !ignoreErrno(xerrno)) {
        debugs(5, 3, "comm_read_try: scheduling Comm::COMM_ERROR");
        ccb->offset = 0;
        ccb->finish(Comm::COMM_ERROR, xerrno);
        return;
    };

    /* Nope, register for some more IO */
    Comm::SetSelect(fd, COMM_SELECT_READ, Comm::HandleRead, data, 0);
}