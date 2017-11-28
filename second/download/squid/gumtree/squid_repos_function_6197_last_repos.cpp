int
logfile_mod_syslog_open(Logfile * lf, const char *path, size_t, int)
{
    lf->f_close = logfile_mod_syslog_close;
    lf->f_linewrite = logfile_mod_syslog_writeline;
    lf->f_linestart = logfile_mod_syslog_linestart;
    lf->f_lineend = logfile_mod_syslog_lineend;
    lf->f_flush = logfile_mod_syslog_flush;
    lf->f_rotate = logfile_mod_syslog_rotate;

    l_syslog_t *ll = static_cast<l_syslog_t*>(xcalloc(1, sizeof(*ll)));
    lf->data = ll;

    ll->syslog_priority = LOG_INFO;

    if (path[6] != '\0') {
        char *priority = xstrdup(path);
        char *facility = (char *) strchr(priority, '.');
        if (!facility)
            facility = (char *) strchr(priority, '|');
        if (facility) {
            *facility = '\0';
            ++facility;
            ll->syslog_priority |= syslog_ntoa(facility);
        }
        ll->syslog_priority |= syslog_ntoa(priority);
        xfree(priority);
        if ((ll->syslog_priority & PRIORITY_MASK) == 0)
            ll->syslog_priority |= LOG_INFO;
    }

    return 1;
}