static void
clientWriteBodyComplete(const Comm::ConnectionPointer &conn, char *buf, size_t size, Comm::Flag errflag, int xerrno, void *data)
{
    debugs(33,7, HERE << "clientWriteBodyComplete schedules clientWriteComplete");
    clientWriteComplete(conn, NULL, size, errflag, xerrno, data);
}