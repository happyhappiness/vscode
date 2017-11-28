void
clientStartListeningOn(AnyP::PortCfgPointer &port, const RefCount< CommCbFunPtrCallT<CommAcceptCbPtrFun> > &subCall, const Ipc::FdNoteId fdNote)
{
    // Fill out a Comm::Connection which IPC will open as a listener for us
    port->listenConn = new Comm::Connection;
    port->listenConn->local = port->s;
    port->listenConn->flags =
        COMM_NONBLOCKING |
        (port->flags.tproxyIntercept ? COMM_TRANSPARENT : 0) |
        (port->flags.natIntercept ? COMM_INTERCEPTION : 0);

    // route new connections to subCall
    typedef CommCbFunPtrCallT<CommAcceptCbPtrFun> AcceptCall;
    Subscription::Pointer sub = new CallSubscription<AcceptCall>(subCall);
    AsyncCall::Pointer listenCall =
        asyncCall(33, 2, "clientListenerConnectionOpened",
                  ListeningStartedDialer(&clientListenerConnectionOpened,
                                         port, fdNote, sub));
    Ipc::StartListening(SOCK_STREAM, IPPROTO_TCP, port->listenConn, fdNote, listenCall);

    assert(NHttpSockets < MAXTCPLISTENPORTS);
    HttpSockets[NHttpSockets] = -1;
    ++NHttpSockets;
}