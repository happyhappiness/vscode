void
fwdConnectDoneWrapper(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno, void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->connectDone(conn, status, xerrno);
}