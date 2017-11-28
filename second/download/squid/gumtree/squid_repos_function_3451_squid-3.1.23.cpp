static void
clientWriteBodyComplete(int fd, char *buf, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    debugs(33,7, HERE << "clientWriteBodyComplete schedules clientWriteComplete");
    clientWriteComplete(fd, NULL, size, errflag, xerrno, data);
}