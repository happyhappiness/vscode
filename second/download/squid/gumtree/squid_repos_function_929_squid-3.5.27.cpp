static void
commSetTcpNoDelay(int fd)
{
    int on = 1;

    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof(on)) < 0)
        debugs(50, DBG_IMPORTANT, "commSetTcpNoDelay: FD " << fd << ": " << xstrerror());

    fd_table[fd].flags.nodelay = true;
}