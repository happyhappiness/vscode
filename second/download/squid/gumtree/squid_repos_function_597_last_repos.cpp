int
commSetNonBlocking(int fd)
{
#if _SQUID_WINDOWS_
    int nonblocking = TRUE;

    if (ioctl(fd, FIONBIO, &nonblocking) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "FD " << fd << ": " << xstrerr(xerrno) << " " << fd_table[fd].type);
        return Comm::COMM_ERROR;
    }

#else
    int flags;
    int dummy = 0;

    if ((flags = fcntl(fd, F_GETFL, dummy)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "FD " << fd << ": fcntl F_GETFL: " << xstrerr(xerrno));
        return Comm::COMM_ERROR;
    }

    if (fcntl(fd, F_SETFL, flags | SQUID_NONBLOCK) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "FD " << fd << ": " << xstrerr(xerrno));
        return Comm::COMM_ERROR;
    }
#endif

    fd_table[fd].flags.nonblocking = true;
    return 0;
}