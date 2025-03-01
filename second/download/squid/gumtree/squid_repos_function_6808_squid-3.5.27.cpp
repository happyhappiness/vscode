void
Ipc::StartListening(int sock_type, int proto, const Comm::ConnectionPointer &listenConn,
                    FdNoteId fdNote, AsyncCall::Pointer &callback)
{
    StartListeningCb *cbd = dynamic_cast<StartListeningCb*>(callback->getDialer());
    Must(cbd);
    cbd->conn = listenConn;

    if (UsingSmp()) { // if SMP is on, share
        OpenListenerParams p;
        p.sock_type = sock_type;
        p.proto = proto;
        p.addr = listenConn->local;
        p.flags = listenConn->flags;
        p.fdNote = fdNote;
        Ipc::JoinSharedListen(p, callback);
        return; // wait for the call back
    }

    enter_suid();
    comm_open_listener(sock_type, proto, cbd->conn, FdNote(fdNote));
    cbd->errNo = Comm::IsConnOpen(cbd->conn) ? 0 : errno;
    leave_suid();

    debugs(54, 3, HERE << "opened listen " << cbd->conn);
    ScheduleCallHere(callback);
}