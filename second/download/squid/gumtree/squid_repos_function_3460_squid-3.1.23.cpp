void
clientWriteComplete(int fd, char *bufnotused, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    ClientSocketContext *context = (ClientSocketContext *)data;
    context->writeComplete (fd, bufnotused, size, errflag);
}