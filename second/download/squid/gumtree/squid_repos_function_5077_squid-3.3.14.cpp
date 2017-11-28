void
Comm::TcpAcceptor::start()
{
    debugs(5, 5, HERE << status() << " AsyncCall Subscription: " << theCallSub);

    Must(IsConnOpen(conn));

    setListen();

    // if no error so far start accepting connections.
    if (errcode == 0)
        SetSelect(conn->fd, COMM_SELECT_READ, doAccept, this, 0);
}