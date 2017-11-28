static void
logfile_mod_udp_writeline(Logfile * lf, const char *buf, size_t len)
{
    l_udp_t *ll = (l_udp_t *) lf->data;

    if (0 == ll->bufsz) {
        /* buffering disabled */
        logfile_mod_udp_write(lf, buf, len);
        return;
    }
    if (ll->offset > 0 && (ll->offset + len + 4) > ll->bufsz)
        logfile_mod_udp_flush(lf);

    if (len > ll->bufsz) {
        /* too big to fit in buffer */
        logfile_mod_udp_write(lf, buf, len);
        return;
    }
    /* buffer it */
    memcpy(ll->buf + ll->offset, buf, len);

    ll->offset += len;

    assert(ll->offset >= 0);

    assert((size_t) ll->offset <= ll->bufsz);
}