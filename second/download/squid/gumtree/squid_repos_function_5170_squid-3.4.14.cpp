void
Comm::TcpAcceptor::notify(const comm_err_t flag, const Comm::ConnectionPointer &newConnDetails) const
{
    // listener socket handlers just abandon the port with COMM_ERR_CLOSING
    // it should only happen when this object is deleted...
    if (flag == COMM_ERR_CLOSING) {
        return;
    }

    if (theCallSub != NULL) {
        AsyncCall::Pointer call = theCallSub->callback();
        CommAcceptCbParams &params = GetCommParams<CommAcceptCbParams>(call);
        params.xaction = new MasterXaction;
        params.xaction->squidPort = static_cast<AnyP::PortCfg*>(params.data);
        params.fd = conn->fd;
        params.conn = params.xaction->tcpClient = newConnDetails;
        params.flag = flag;
        params.xerrno = errcode;
        ScheduleCallHere(call);
    }
}