void
Comm::TcpAcceptor::notify(const Comm::Flag flag, const Comm::ConnectionPointer &newConnDetails) const
{
    // listener socket handlers just abandon the port with Comm::ERR_CLOSING
    // it should only happen when this object is deleted...
    if (flag == Comm::ERR_CLOSING) {
        return;
    }

    if (theCallSub != NULL) {
        AsyncCall::Pointer call = theCallSub->callback();
        CommAcceptCbParams &params = GetCommParams<CommAcceptCbParams>(call);
        params.xaction = new MasterXaction;
        params.xaction->squidPort = listenPort_;
        params.fd = conn->fd;
        params.conn = params.xaction->tcpClient = newConnDetails;
        params.flag = flag;
        params.xerrno = errcode;
        ScheduleCallHere(call);
    }
}