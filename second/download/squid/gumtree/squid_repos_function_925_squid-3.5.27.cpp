static void
commSetTcpRcvbuf(int fd, int size)
{
    if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (char *) &size, sizeof(size)) < 0)
        debugs(50, DBG_IMPORTANT, "commSetTcpRcvbuf: FD " << fd << ", SIZE " << size << ": " << xstrerror());
    if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char *) &size, sizeof(size)) < 0)
        debugs(50, DBG_IMPORTANT, "commSetTcpRcvbuf: FD " << fd << ", SIZE " << size << ": " << xstrerror());
#ifdef TCP_WINDOW_CLAMP
    if (setsockopt(fd, SOL_TCP, TCP_WINDOW_CLAMP, (char *) &size, sizeof(size)) < 0)
        debugs(50, DBG_IMPORTANT, "commSetTcpRcvbuf: FD " << fd << ", SIZE " << size << ": " << xstrerror());
#endif
}