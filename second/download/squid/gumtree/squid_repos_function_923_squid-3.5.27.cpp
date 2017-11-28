static void
commSetNoLinger(int fd)
{

    struct linger L;
    L.l_onoff = 0;      /* off */
    L.l_linger = 0;

    if (setsockopt(fd, SOL_SOCKET, SO_LINGER, (char *) &L, sizeof(L)) < 0)
        debugs(50, 0, "commSetNoLinger: FD " << fd << ": " << xstrerror());

    fd_table[fd].flags.nolinger = true;
}