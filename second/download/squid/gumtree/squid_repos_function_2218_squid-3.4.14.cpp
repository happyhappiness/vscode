static void
fwdNegotiateSSLWrapper(int fd, void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->negotiateSSL(fd);
}