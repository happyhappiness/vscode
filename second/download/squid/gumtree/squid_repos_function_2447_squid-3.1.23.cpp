void
logfileClose(Logfile * lf)
{
    logfileFlush(lf);

    if (lf->fd >= 0)
        file_close(lf->fd);

    if (lf->buf)
        xfree(lf->buf);

    xfree(lf);
}