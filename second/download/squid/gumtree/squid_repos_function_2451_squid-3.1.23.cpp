void
logfileFlush(Logfile * lf)
{
    if (0 == lf->offset)
        return;

    logfileWriteWrapper(lf, lf->buf, (size_t) lf->offset);

    lf->offset = 0;
}