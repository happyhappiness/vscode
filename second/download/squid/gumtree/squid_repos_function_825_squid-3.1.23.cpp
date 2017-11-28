static void
whoisWriteComplete(int fd, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    xfree(buf);
}