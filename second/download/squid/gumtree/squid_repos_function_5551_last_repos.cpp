Comm::Flag
Comm::ReadNow(CommIoCbParams &params, SBuf &buf)
{
    /* Attempt a read */
    ++ statCounter.syscalls.sock.reads;
    SBuf::size_type sz = buf.spaceSize();
    if (params.size > 0 && params.size < sz)
        sz = params.size;
    char *inbuf = buf.rawSpace(sz);
    errno = 0;
    const int retval = FD_READ_METHOD(params.conn->fd, inbuf, sz);
    params.xerrno = errno;

    debugs(5, 3, params.conn << ", size " << sz << ", retval " << retval << ", errno " << params.xerrno);

    if (retval > 0) { // data read most common case
        buf.append(inbuf, retval);
        fd_bytes(params.conn->fd, retval, FD_READ);
        params.flag = Comm::OK;
        params.size = retval;

    } else if (retval == 0) { // remote closure (somewhat less) common
        // Note - read 0 == socket EOF, which is a valid read.
        params.flag = Comm::ENDFILE;

    } else if (retval < 0) { // connection errors are worst-case
        debugs(5, 3, params.conn << " Comm::COMM_ERROR: " << xstrerr(params.xerrno));
        if (ignoreErrno(params.xerrno))
            params.flag =  Comm::INPROGRESS;
        else
            params.flag =  Comm::COMM_ERROR;
    }

    return params.flag;
}