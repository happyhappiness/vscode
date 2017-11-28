void
old_comm_reset_close(int fd)
{
    struct linger L;
    L.l_onoff = 1;
    L.l_linger = 0;

    if (setsockopt(fd, SOL_SOCKET, SO_LINGER, (char *) &L, sizeof(L)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, "ERROR: Closing FD " << fd << " with TCP RST: " << xstrerr(xerrno));
    }
    comm_close(fd);
}