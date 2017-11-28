static void
commHandleWrite(int fd, void *data)
{
    comm_io_callback_t *state = (comm_io_callback_t *)data;
    int len = 0;
    int nleft;

    assert(state == COMMIO_FD_WRITECB(fd));

    PROF_start(commHandleWrite);
    debugs(5, 5, "commHandleWrite: FD " << fd << ": off " <<
           (long int) state->offset << ", sz " << (long int) state->size << ".");

    nleft = state->size - state->offset;
    len = FD_WRITE_METHOD(fd, state->buf + state->offset, nleft);
    debugs(5, 5, "commHandleWrite: write() returns " << len);
    fd_bytes(fd, len, FD_WRITE);
    statCounter.syscalls.sock.writes++;

    if (len == 0) {
        /* Note we even call write if nleft == 0 */
        /* We're done */

        if (nleft != 0)
            debugs(5, 1, "commHandleWrite: FD " << fd << ": write failure: connection closed with " << nleft << " bytes remaining.");

        commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_ERROR : COMM_OK, errno);
    } else if (len < 0) {
        /* An error */

        if (fd_table[fd].flags.socket_eof) {
            debugs(50, 2, "commHandleWrite: FD " << fd << ": write failure: " << xstrerror() << ".");
            commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_ERROR : COMM_OK, errno);
        } else if (ignoreErrno(errno)) {
            debugs(50, 10, "commHandleWrite: FD " << fd << ": write failure: " << xstrerror() << ".");
            commSetSelect(fd,
                          COMM_SELECT_WRITE,
                          commHandleWrite,
                          state,
                          0);
        } else {
            debugs(50, 2, "commHandleWrite: FD " << fd << ": write failure: " << xstrerror() << ".");
            commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_ERROR : COMM_OK, errno);
        }
    } else {
        /* A successful write, continue */
        state->offset += len;

        if (state->offset < state->size) {
            /* Not done, reinstall the write handler and write some more */
            commSetSelect(fd,
                          COMM_SELECT_WRITE,
                          commHandleWrite,
                          state,
                          0);
        } else {
            commio_finish_callback(fd, COMMIO_FD_WRITECB(fd), nleft ? COMM_OK : COMM_ERROR, errno);
        }
    }

    PROF_stop(commHandleWrite);
}