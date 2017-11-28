static void
logfile_mod_daemon_writeline(Logfile * lf, const char *buf, size_t len)
{
    l_daemon_t *ll = static_cast<l_daemon_t *>(lf->data);
    /* Make sure the logfile buffer isn't too large */
    if (ll->nbufs > LOGFILE_MAXBUFS) {
        if (ll->last_warned < squid_curtime - LOGFILE_WARN_TIME) {
            ll->last_warned = squid_curtime;
            debugs(50, DBG_IMPORTANT, "Logfile: " << lf->path << ": queue is too large; some log messages have been lost.");
        }
        return;
    }
    /* Append this data to the end buffer; create a new one if needed */
    /* Are we eol? If so, prefix with our logfile command byte */
    logfile_mod_daemon_append(lf, buf, len);
}