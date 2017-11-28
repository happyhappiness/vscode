static void
logfile_mod_daemon_append(Logfile * lf, const char *buf, int len)
{
    l_daemon_t *ll = (l_daemon_t *) lf->data;
    logfile_buffer_t *b;
    int s;

    /* Is there a buffer? If not, create one */
    if (ll->bufs.head == NULL) {
        logfileNewBuffer(lf);
    }
    debugs(50, 3, "logfile_mod_daemon_append: " << lf->path << ": appending " << len << " bytes");
    /* Copy what can be copied */
    while (len > 0) {
        b = static_cast<logfile_buffer_t*>(ll->bufs.tail->data);
        debugs(50, 3, "logfile_mod_daemon_append: current buffer has " << b->len << " of " << b->size << " bytes before append");
        s = min(len, (b->size - b->len));
        memcpy(b->buf + b->len, buf, s);
        len = len - s;
        buf = buf + s;
        b->len = b->len + s;
        assert(b->len <= LOGFILE_BUFSZ);
        assert(len >= 0);
        if (len > 0) {
            logfileNewBuffer(lf);
        }
    }
}