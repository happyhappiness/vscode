static void
logfile_mod_tcp_close(Logfile * lf)
{
    l_tcp_t *ll = (l_tcp_t *) lf->data;
    lf->f_flush(lf);

    if (ll->fd >= 0)
        file_close(ll->fd);

    if (ll->buf)
        xfree(ll->buf);

    xfree(lf->data);
    lf->data = NULL;
}