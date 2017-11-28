static void
logfile_mod_tcp_write(Logfile * lf, const char *buf, size_t len)
{
    l_tcp_t *ll = (l_tcp_t *) lf->data;
    ssize_t s;
    s = write(ll->fd, (char const *) buf, len);

    fd_bytes(ll->fd, s, FD_WRITE);
#if 0
    if (s < 0) {
        debugs(1, DBG_IMPORTANT, "logfile (tcp): got errno (" << errno << "):" << xstrerror());
    }
    if (s != len) {
        debugs(1, DBG_IMPORTANT, "logfile (tcp): len=" << len << ", wrote=" << s);
    }
#endif

    /* We don't worry about network errors for now */
}