static void
whoisWriteComplete(const Comm::ConnectionPointer &, char *buf, size_t size, Comm::Flag flag, int xerrno, void *data)
{
    xfree(buf);
}