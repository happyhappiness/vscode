static void
logfile_mod_tcp_flush(Logfile * lf)
{
    l_tcp_t *ll = (l_tcp_t *) lf->data;
    if (0 == ll->offset)
        return;
    logfile_mod_tcp_write(lf, ll->buf, (size_t) ll->offset);
    ll->offset = 0;
}