void
commSetCloseOnExec(int fd)
{
#ifdef FD_CLOEXEC
    int flags;
    int dummy = 0;

    if ((flags = fcntl(fd, F_GETFD, dummy)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "FD " << fd << ": fcntl F_GETFD: " << xstrerr(xerrno));
        return;
    }

    if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "FD " << fd << ": set close-on-exec failed: " << xstrerr(xerrno));
    }

    fd_table[fd].flags.close_on_exec = true;

#endif
}