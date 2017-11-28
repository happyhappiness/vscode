static void
commSetTcpRcvbuf(int fd, int size)
{
    if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (char *) &size, sizeof(size)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, MYNAME << "FD " << fd << ", SIZE " << size << ": " << xstrerr(xerrno));
    }
    if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char *) &size, sizeof(size)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, MYNAME << "FD " << fd << ", SIZE " << size << ": " << xstrerr(xerrno));
    }
#ifdef TCP_WINDOW_CLAMP
    if (setsockopt(fd, SOL_TCP, TCP_WINDOW_CLAMP, (char *) &size, sizeof(size)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, MYNAME << "FD " << fd << ", SIZE " << size << ": " << xstrerr(xerrno));
    }
#endif
}