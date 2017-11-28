static void
logfile_mod_udp_flush(Logfile * lf)
{
    l_udp_t *ll = (l_udp_t *) lf->data;
    if (0 == ll->offset)
        return;
    logfile_mod_udp_write(lf, ll->buf, (size_t) ll->offset);
    ll->offset = 0;
}