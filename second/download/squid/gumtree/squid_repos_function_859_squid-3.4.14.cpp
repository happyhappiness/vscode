static void
whoisReadReply(const Comm::ConnectionPointer &conn, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    WhoisState *p = (WhoisState *)data;
    p->readReply(conn, buf, len, flag, xerrno);
}