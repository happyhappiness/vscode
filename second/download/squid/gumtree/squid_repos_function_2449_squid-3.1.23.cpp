void
logfileWrite(Logfile * lf, void *buf, size_t len)
{
#if HAVE_SYSLOG

    if (lf->flags.syslog) {
        syslog(lf->syslog_priority, "%s", (char *)buf);
        return;
    }

#endif

    if (0 == lf->bufsz) {
        /* buffering disabled */
        logfileWriteWrapper(lf, buf, len);
        return;
    }

    if (lf->offset > 0 && lf->offset + len > lf->bufsz)
        logfileFlush(lf);

    if (len > lf->bufsz) {
        /* too big to fit in buffer */
        logfileWriteWrapper(lf, buf, len);
        return;
    }

    /* buffer it */
    xmemcpy(lf->buf + lf->offset, buf, len);

    lf->offset += len;

    assert (lf->offset >= 0);

    assert((size_t)lf->offset <= lf->bufsz);
}