static void
commSetTcpNoDelay(int fd)
{
    int on = 1;

    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &on, sizeof(on)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, MYNAME << "FD " << fd << ": " << xstrerr(xerrno));
    }

    fd_table[fd].flags.nodelay = true;
}