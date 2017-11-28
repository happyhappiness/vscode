static void
fwdServerClosedWrapper(int fd, void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->serverClosed(fd);
}