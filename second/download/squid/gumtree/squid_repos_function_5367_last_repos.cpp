static void
ftpOpenListenSocket(Ftp::Gateway * ftpState, int fallback)
{
    /// Close old data channels, if any. We may open a new one below.
    if (ftpState->data.conn != NULL) {
        if ((ftpState->data.conn->flags & COMM_REUSEADDR))
            // NP: in fact it points to the control channel. just clear it.
            ftpState->data.clear();
        else
            ftpState->data.close();
    }
    safe_free(ftpState->data.host);

    if (!Comm::IsConnOpen(ftpState->ctrl.conn)) {
        debugs(9, 5, "The control connection to the remote end is closed");
        return;
    }

    /*
     * Set up a listen socket on the same local address as the
     * control connection.
     */
    Comm::ConnectionPointer temp = new Comm::Connection;
    temp->local = ftpState->ctrl.conn->local;

    /*
     * REUSEADDR is needed in fallback mode, since the same port is
     * used for both control and data.
     */
    if (fallback) {
        int on = 1;
        errno = 0;
        if (setsockopt(ftpState->ctrl.conn->fd, SOL_SOCKET, SO_REUSEADDR,
                       (char *) &on, sizeof(on)) == -1) {
            int xerrno = errno;
            // SO_REUSEADDR is only an optimization, no need to be verbose about error
            debugs(9, 4, "setsockopt failed: " << xstrerr(xerrno));
        }
        ftpState->ctrl.conn->flags |= COMM_REUSEADDR;
        temp->flags |= COMM_REUSEADDR;
    } else {
        /* if not running in fallback mode a new port needs to be retrieved */
        temp->local.port(0);
    }

    ftpState->listenForDataChannel(temp);
}