void
ClientSocketContext::WroteControlMsg(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    ClientSocketContext *context = static_cast<ClientSocketContext*>(data);
    context->wroteControlMsg(conn, bufnotused, size, errflag, xerrno);
}