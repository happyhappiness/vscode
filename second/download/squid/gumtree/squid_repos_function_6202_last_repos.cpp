static void
logfile_mod_stdio_flush(Logfile * lf)
{
    l_stdio_t *ll = (l_stdio_t *) lf->data;
    if (0 == ll->offset)
        return;
    logfileWriteWrapper(lf, ll->buf, (size_t) ll->offset);
    ll->offset = 0;
}