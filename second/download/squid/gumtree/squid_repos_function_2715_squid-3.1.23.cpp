static void
tunnelProxyConnectedWriteDone(int fd, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    tunnelConnectedWriteDone(fd, buf, size, flag, xerrno, data);
}