Comm::ConnectionPointer
Ipc::Coordinator::openListenSocket(const SharedListenRequest& request,
                                   int &errNo)
{
    const OpenListenerParams &p = request.params;

    debugs(54, 6, HERE << "opening listen FD at " << p.addr << " for kid" <<
           request.requestorId);

    Comm::ConnectionPointer conn = new Comm::Connection;
    conn->local = p.addr; // comm_open_listener may modify it
    conn->flags = p.flags;

    enter_suid();
    comm_open_listener(p.sock_type, p.proto, conn, FdNote(p.fdNote));
    errNo = Comm::IsConnOpen(conn) ? 0 : errno;
    leave_suid();

    debugs(54, 6, HERE << "tried listening on " << conn << " for kid" <<
           request.requestorId);

    // cache positive results
    if (Comm::IsConnOpen(conn))
        listeners[request.params] = conn;

    return conn;
}