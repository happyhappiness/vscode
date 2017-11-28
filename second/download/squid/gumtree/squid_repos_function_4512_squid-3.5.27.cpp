bool
Ssl::PeerConnector::prepareSocket()
{
    const int fd = serverConnection()->fd;
    if (!Comm::IsConnOpen(serverConn) || fd_table[serverConn->fd].closing()) {
        connectionClosed("Ssl::PeerConnector::prepareSocket");
        return false;
    }

    // watch for external connection closures
    typedef CommCbMemFunT<Ssl::PeerConnector, CommCloseCbParams> Dialer;
    closeHandler = JobCallback(9, 5, Dialer, this, Ssl::PeerConnector::commCloseHandler);
    comm_add_close_handler(fd, closeHandler);
    return true;
}