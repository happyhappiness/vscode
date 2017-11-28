static void
logfile_mod_udp_close(Logfile * lf)
{
    l_udp_t *ll = (l_udp_t *) lf->data;
    lf->f_flush(lf);

    if (ll->fd >= 0)
        file_close(ll->fd);

    if (ll->buf)
        xfree(ll->buf);

    xfree(lf->data);
    lf->data = NULL;
}