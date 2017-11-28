static void
commSetReuseAddr(int fd)
{
    int on = 1;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0)
        debugs(50, 1, "commSetReuseAddr: FD " << fd << ": " << xstrerror());
}