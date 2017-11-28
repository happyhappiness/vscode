static void
logfile_mod_syslog_writeline(Logfile * lf, const char *buf, size_t)
{
    l_syslog_t *ll = (l_syslog_t *) lf->data;
    syslog(ll->syslog_priority, "%s", (char *) buf);
}