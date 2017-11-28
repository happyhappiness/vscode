int
commSetNonBlocking(int fd)
{
#ifndef _SQUID_MSWIN_
    int flags;
    int dummy = 0;
#endif
#ifdef _SQUID_WIN32_

    int nonblocking = TRUE;

#ifdef _SQUID_CYGWIN_

    if (fd_table[fd].type != FD_PIPE) {
#endif

        if (ioctl(fd, FIONBIO, &nonblocking) < 0) {
            debugs(50, 0, "commSetNonBlocking: FD " << fd << ": " << xstrerror() << " " << fd_table[fd].type);
            return COMM_ERROR;
        }

#ifdef _SQUID_CYGWIN_

    } else {
#endif
#endif
#ifndef _SQUID_MSWIN_

        if ((flags = fcntl(fd, F_GETFL, dummy)) < 0) {
            debugs(50, 0, "FD " << fd << ": fcntl F_GETFL: " << xstrerror());
            return COMM_ERROR;
        }

        if (fcntl(fd, F_SETFL, flags | SQUID_NONBLOCK) < 0) {
            debugs(50, 0, "commSetNonBlocking: FD " << fd << ": " << xstrerror());
            return COMM_ERROR;
        }

#endif
#ifdef _SQUID_CYGWIN_

    }

#endif
    fd_table[fd].flags.nonblocking = 1;

    return 0;
}