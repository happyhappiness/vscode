static void
commHalfClosedReader(int fd, char *, size_t size, comm_err_t flag, int, void *)
{
    // there cannot be more data coming in on half-closed connections
    assert(size == 0);
    assert(commHasHalfClosedMonitor(fd)); // or we would have canceled the read

    fd_table[fd].halfClosedReader = NULL; // done reading, for now

    // nothing to do if fd is being closed
    if (flag == COMM_ERR_CLOSING)
        return;

    // if read failed, close the connection
    if (flag != COMM_OK) {
        debugs(5, 3, "commHalfClosedReader: closing FD " << fd);
        comm_close(fd);
        return;
    }

    // continue waiting for close or error
    commPlanHalfClosedCheck(); // make sure this fd will be checked again
}