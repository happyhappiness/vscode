static void
commSetNoLinger(int fd)
{

    struct linger L;
    L.l_onoff = 0;      /* off */
    L.l_linger = 0;

    if (setsockopt(fd, SOL_SOCKET, SO_LINGER, (char *) &L, sizeof(L)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << "FD " << fd << ": " << xstrerr(xerrno));
    }
    fd_table[fd].flags.nolinger = true;
}