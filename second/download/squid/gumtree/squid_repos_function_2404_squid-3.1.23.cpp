static void
fwdConnectTimeoutWrapper(int fd, void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->connectTimeout(fd);
}