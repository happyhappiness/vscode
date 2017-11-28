static void
logfileWriteWrapper(Logfile * lf, const void *buf, size_t len)
{
    l_stdio_t *ll = (l_stdio_t *) lf->data;
    size_t s;
    s = FD_WRITE_METHOD(ll->fd, (char const *) buf, len);
    fd_bytes(ll->fd, s, FD_WRITE);

    if (s == len)
        return;

    if (!lf->flags.fatal)
        return;

    fatalf("logfileWrite: %s: %s\n", lf->path, xstrerror());
}