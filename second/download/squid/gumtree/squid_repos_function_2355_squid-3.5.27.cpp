void
fwdConnectDoneWrapper(const Comm::ConnectionPointer &conn, Comm::Flag status, int xerrno, void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->connectDone(conn, status, xerrno);
}