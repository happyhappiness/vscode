int
commSetNonBlocking(int fd)
{
#if _SQUID_WINDOWS_
    int nonblocking = TRUE;

    if (ioctl(fd, FIONBIO, &nonblocking) < 0) {
        debugs(50, 0, "commSetNonBlocking: FD " << fd << ": " << xstrerror() << " " << fd_table[fd].type);
        return Comm::COMM_ERROR;
    }

#else
    int flags;
    int dummy = 0;

    if ((flags = fcntl(fd, F_GETFL, dummy)) < 0) {
        debugs(50, 0, "FD " << fd << ": fcntl F_GETFL: " << xstrerror());
        return Comm::COMM_ERROR;
    }

    if (fcntl(fd, F_SETFL, flags | SQUID_NONBLOCK) < 0) {
        debugs(50, 0, "commSetNonBlocking: FD " << fd << ": " << xstrerror());
        return Comm::COMM_ERROR;
    }
#endif

    fd_table[fd].flags.nonblocking = true;
    return 0;
}