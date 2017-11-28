void
FtpStateData::listenForDataChannel(const Comm::ConnectionPointer &conn, const char *note)
{
    assert(!Comm::IsConnOpen(data.conn));

    typedef CommCbMemFunT<FtpStateData, CommAcceptCbParams> AcceptDialer;
    typedef AsyncCallT<AcceptDialer> AcceptCall;
    RefCount<AcceptCall> call = static_cast<AcceptCall*>(JobCallback(11, 5, AcceptDialer, this, FtpStateData::ftpAcceptDataConnection));
    Subscription::Pointer sub = new CallSubscription<AcceptCall>(call);

    /* open the conn if its not already open */
    if (!Comm::IsConnOpen(conn)) {
        conn->fd = comm_open_listener(SOCK_STREAM, IPPROTO_TCP, conn->local, conn->flags, note);
        if (!Comm::IsConnOpen(conn)) {
            debugs(5, DBG_CRITICAL, HERE << "comm_open_listener failed:" << conn->local << " error: " << errno);
            return;
        }
        debugs(9, 3, HERE << "Unconnected data socket created on " << conn);
    }

    assert(Comm::IsConnOpen(conn));
    AsyncJob::Start(new Comm::TcpAcceptor(conn, note, sub));

    // Ensure we have a copy of the FD opened for listening and a close handler on it.
    data.opened(conn, dataCloser());
    switchTimeoutToDataChannel();
}