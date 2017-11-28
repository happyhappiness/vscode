static bool
writeTimedOut(int fd)
{
    if (!COMMIO_FD_WRITECB(fd)->active())
        return false;

    if ((squid_curtime - fd_table[fd].writeStart) < Config.Timeout.write)
        return false;

    return true;
}