Comm::ConnectionPointer
Ipc::Coordinator::openListenSocket(const SharedListenRequest& request,
                                   int &errNo)
{
    const OpenListenerParams &p = request.params;

    debugs(54, 6, HERE << "opening listen FD at " << p.addr << " for kid" <<
           request.requestorId);

    Comm::ConnectionPointer newConn = new Comm::Connection;
    newConn->local = p.addr; // comm_open_listener may modify it
    newConn->flags = p.flags;

    enter_suid();
    comm_open_listener(p.sock_type, p.proto, newConn, FdNote(p.fdNote));
    errNo = Comm::IsConnOpen(newConn) ? 0 : errno;
    leave_suid();

    debugs(54, 6, HERE << "tried listening on " << newConn << " for kid" <<
           request.requestorId);

    // cache positive results
    if (Comm::IsConnOpen(newConn))
        listeners[request.params] = newConn;

    return newConn;
}