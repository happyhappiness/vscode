void
logfileWrite(Logfile * lf, char *buf, size_t len)
{
    lf->f_linewrite(lf, buf, len);
}