void
_db_init(const char *logfile, const char *options)
{
    Debug::parseOptions(options);

    debugOpenLog(logfile);

#if HAVE_SYSLOG && defined(LOG_LOCAL4)

    if (Debug::log_syslog)
        openlog(APP_SHORTNAME, LOG_PID | LOG_NDELAY | LOG_CONS, syslog_facility);

#endif /* HAVE_SYSLOG */

    /* Pre-Init TZ env, see bug #2656 */
    tzset();
}