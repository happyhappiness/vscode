static void
logfileWriteWrapper(Logfile * lf, const void *buf, size_t len)
{
    size_t s;
    s = FD_WRITE_METHOD(lf->fd, (char const *)buf, len);
    fd_bytes(lf->fd, s, FD_WRITE);

    if (s == len)
        return;

    if (!lf->flags.fatal)
        return;

    fatalf("logfileWrite: %s: %s\n", lf->path, xstrerror());
}