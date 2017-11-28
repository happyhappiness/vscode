void
fd_open(int fd, CB * cb, void *data, CB * ccb)
{
    assert(fd < SQUID_MAXFD);
    FD[fd].cb = cb;
    FD[fd].ccb = ccb;
    FD[fd].data = data;
    FD[fd].start = now.tv_sec;
    if (fd > maxfd)
        maxfd = fd;
    nfds++;
}