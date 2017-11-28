unsigned int
Ftp::Server::listenForDataConnection()
{
    closeDataConnection();

    Comm::ConnectionPointer conn = new Comm::Connection;
    conn->flags = COMM_NONBLOCKING;
    conn->local = transparent() ? port->s : clientConnection->local;
    conn->local.port(0);
    const char *const note = uri.c_str();
    comm_open_listener(SOCK_STREAM, IPPROTO_TCP, conn, note);
    if (!Comm::IsConnOpen(conn)) {
        debugs(5, DBG_CRITICAL, "comm_open_listener failed for FTP data: " <<
               conn->local << " error: " << errno);
        writeCustomReply(451, "Internal error");
        return 0;
    }

    typedef CommCbMemFunT<Server, CommAcceptCbParams> AcceptDialer;
    typedef AsyncCallT<AcceptDialer> AcceptCall;
    RefCount<AcceptCall> call = static_cast<AcceptCall*>(JobCallback(5, 5, AcceptDialer, this, Ftp::Server::acceptDataConnection));
    Subscription::Pointer sub = new CallSubscription<AcceptCall>(call);
    listener = call.getRaw();
    dataListenConn = conn;
    AsyncJob::Start(new Comm::TcpAcceptor(conn, note, sub));

    const unsigned int listeningPort = comm_local_port(conn->fd);
    conn->local.port(listeningPort);
    return listeningPort;
}