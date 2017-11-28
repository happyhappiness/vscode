int
commSetNonBlocking(int fd)
{
#if !_SQUID_WINDOWS_
    int flags;
    int dummy = 0;
#endif
#if _SQUID_WINDOWS_
    int nonblocking = TRUE;

#if _SQUID_CYGWIN_
    if (fd_table[fd].type != FD_PIPE) {
#endif

        if (ioctl(fd, FIONBIO, &nonblocking) < 0) {
            debugs(50, 0, "commSetNonBlocking: FD " << fd << ": " << xstrerror() << " " << fd_table[fd].type);
            return COMM_ERROR;
        }

#if _SQUID_CYGWIN_
    } else {
#endif
#endif
#if !_SQUID_WINDOWS_

        if ((flags = fcntl(fd, F_GETFL, dummy)) < 0) {
            debugs(50, 0, "FD " << fd << ": fcntl F_GETFL: " << xstrerror());
            return COMM_ERROR;
        }

        if (fcntl(fd, F_SETFL, flags | SQUID_NONBLOCK) < 0) {
            debugs(50, 0, "commSetNonBlocking: FD " << fd << ": " << xstrerror());
            return COMM_ERROR;
        }

#endif
#if _SQUID_CYGWIN_
    }
#endif
    fd_table[fd].flags.nonblocking = 1;

    return 0;
}