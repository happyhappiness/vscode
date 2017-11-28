static void
whoisWriteComplete(const Comm::ConnectionPointer &, char *buf, size_t, Comm::Flag, int, void *)
{
    xfree(buf);
}