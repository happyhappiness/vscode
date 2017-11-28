static void
commHalfClosedReader(const Comm::ConnectionPointer &conn, char *, size_t size, Comm::Flag flag, int, void *)
{
    // there cannot be more data coming in on half-closed connections
    assert(size == 0);
    assert(conn != NULL);
    assert(commHasHalfClosedMonitor(conn->fd)); // or we would have canceled the read

    fd_table[conn->fd].halfClosedReader = NULL; // done reading, for now

    // nothing to do if fd is being closed
    if (flag == Comm::ERR_CLOSING)
        return;

    // if read failed, close the connection
    if (flag != Comm::OK) {
        debugs(5, 3, HERE << "closing " << conn);
        conn->close();
        return;
    }

    // continue waiting for close or error
    commPlanHalfClosedCheck(); // make sure this fd will be checked again
}