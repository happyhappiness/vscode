    return ANET_OK;
}

static int _anetTcpNoDelay(char *err, int fd, int yes) 
{
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1)
    {
        anetSetError(err, "setsockopt TCP_NODELAY: %s", strerror(errno));
