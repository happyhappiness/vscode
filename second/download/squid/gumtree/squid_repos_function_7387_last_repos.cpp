bool
Security::PeerConnector::prepareSocket()
{
    debugs(83, 5, serverConnection() << ", this=" << (void*)this);
    if (!Comm::IsConnOpen(serverConnection()) || fd_table[serverConnection()->fd].closing()) {
        connectionClosed("Security::PeerConnector::prepareSocket");
        return false;
    }

    debugs(83, 5, serverConnection());

    // watch for external connection closures
    typedef CommCbMemFunT<Security::PeerConnector, CommCloseCbParams> Dialer;
    closeHandler = JobCallback(9, 5, Dialer, this, Security::PeerConnector::commCloseHandler);
    comm_add_close_handler(serverConnection()->fd, closeHandler);
    return true;
}