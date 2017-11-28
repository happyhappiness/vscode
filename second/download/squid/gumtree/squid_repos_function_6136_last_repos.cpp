static void
logfile_mod_udp_write(Logfile * lf, const char *buf, size_t len)
{
    l_udp_t *ll = (l_udp_t *) lf->data;
    ssize_t s;
    s = write(ll->fd, (char const *) buf, len);
    fd_bytes(ll->fd, s, FD_WRITE);
#if 0
    if (s < 0) {
        int xerrno = errno;
        debugs(1, DBG_IMPORTANT, "logfile (udp): got errno (" << errno << "):" << xstrerr(xerrno));
    }
    if (s != len) {
        debugs(1, DBG_IMPORTANT, "logfile (udp): len=" << len << ", wrote=" << s);
    }
#endif

    /* We don't worry about network errors for now */
}