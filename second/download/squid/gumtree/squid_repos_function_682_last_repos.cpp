static void
_db_print_syslog(const char *format, va_list args)
{
    /* level 0,1 go to syslog */

    if (Debug::Level() > 1)
        return;

    if (!Debug::log_syslog)
        return;

    char tmpbuf[BUFSIZ];
    tmpbuf[0] = '\0';

    vsnprintf(tmpbuf, BUFSIZ, format, args);

    tmpbuf[BUFSIZ - 1] = '\0';

    syslog(Debug::Level() == 0 ? LOG_WARNING : LOG_NOTICE, "%s", tmpbuf);
}