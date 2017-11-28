static void
whoisReadReply(int fd, char *buf, size_t len, comm_err_t flag, int xerrno, void *data)
{
    WhoisState *p = (WhoisState *)data;
    p->readReply(fd, buf, len, flag, xerrno);
}