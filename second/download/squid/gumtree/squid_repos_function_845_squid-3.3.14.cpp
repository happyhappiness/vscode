static void
whoisWriteComplete(const Comm::ConnectionPointer &, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    xfree(buf);
}