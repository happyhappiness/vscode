static void
logfile_mod_stdio_lineend(Logfile * lf)
{
    lf->f_flush(lf);
}