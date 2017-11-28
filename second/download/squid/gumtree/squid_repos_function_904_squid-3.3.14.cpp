void
commSetTcpKeepalive(int fd, int idle, int interval, int timeout)
{
    int on = 1;
#ifdef TCP_KEEPCNT
    if (timeout && interval) {
        int count = (timeout + interval - 1) / interval;
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(on)) < 0)
            debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
#ifdef TCP_KEEPIDLE
    if (idle) {
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(on)) < 0)
            debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
#ifdef TCP_KEEPINTVL
    if (interval) {
        if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(on)) < 0)
            debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
    }
#endif
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *) &on, sizeof(on)) < 0)
        debugs(5, DBG_IMPORTANT, "commSetKeepalive: FD " << fd << ": " << xstrerror());
}