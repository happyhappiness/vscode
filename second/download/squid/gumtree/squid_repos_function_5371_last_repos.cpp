void
Ftp::Gateway::ftpAcceptDataConnection(const CommAcceptCbParams &io)
{
    debugs(9, 3, HERE);

    if (!Comm::IsConnOpen(ctrl.conn)) { /*Close handlers will cleanup*/
        debugs(9, 5, "The control connection to the remote end is closed");
        return;
    }

    if (io.flag != Comm::OK) {
        data.listenConn->close();
        data.listenConn = NULL;
        debugs(9, DBG_IMPORTANT, "FTP AcceptDataConnection: " << io.conn << ": " << xstrerr(io.xerrno));
        /** \todo Need to send error message on control channel*/
        ftpFail(this);
        return;
    }

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortAll("entry aborted when accepting data conn");
        data.listenConn->close();
        data.listenConn = NULL;
        io.conn->close();
        return;
    }

    /* data listening conn is no longer even open. abort. */
    if (!Comm::IsConnOpen(data.listenConn)) {
        data.listenConn = NULL; // ensure that it's cleared and not just closed.
        return;
    }

    /* data listening conn is no longer even open. abort. */
    if (!Comm::IsConnOpen(data.conn)) {
        data.clear(); // ensure that it's cleared and not just closed.
        return;
    }

    /** \par
     * When squid.conf ftp_sanitycheck is enabled, check the new connection is actually being
     * made by the remote client which is connected to the FTP control socket.
     * Or the one which we were told to listen for by control channel messages (may differ under NAT).
     * This prevents third-party hacks, but also third-party load balancing handshakes.
     */
    if (Config.Ftp.sanitycheck) {
        // accept if either our data or ctrl connection is talking to this remote peer.
        if (data.conn->remote != io.conn->remote && ctrl.conn->remote != io.conn->remote) {
            debugs(9, DBG_IMPORTANT,
                   "FTP data connection from unexpected server (" <<
                   io.conn->remote << "), expecting " <<
                   data.conn->remote << " or " << ctrl.conn->remote);

            /* close the bad sources connection down ASAP. */
            io.conn->close();

            /* drop the bad connection (io) by ignoring the attempt. */
            return;
        }
    }

    /** On Comm::OK start using the accepted data socket and discard the temporary listen socket. */
    data.close();
    data.opened(io.conn, dataCloser());
    data.addr(io.conn->remote);

    debugs(9, 3, HERE << "Connected data socket on " <<
           io.conn << ". FD table says: " <<
           "ctrl-peer= " << fd_table[ctrl.conn->fd].ipaddr << ", " <<
           "data-peer= " << fd_table[data.conn->fd].ipaddr);

    assert(haveControlChannel("ftpAcceptDataConnection"));
    assert(ctrl.message == NULL);

    // Ctrl channel operations will determine what happens to this data connection
}