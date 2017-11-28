void
logfileFlush(Logfile * lf)
{
    lf->f_flush(lf);
}