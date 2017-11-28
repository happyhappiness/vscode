static void
logfile_mod_syslog_close(Logfile *lf)
{
    xfree(lf->data);
    lf->data = NULL;
}