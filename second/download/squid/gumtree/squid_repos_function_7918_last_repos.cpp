void
syslog(int priority, const char *fmt, ...)
{
    WORD logtype;
    char *str=static_cast<char *>(xmalloc(SYSLOG_MAX_MSG_SIZE));
    int str_len;
    va_list ap;

    if (!ms_eventlog)
        return;

    va_start(ap, fmt);
    str_len = vsnprintf(str, SYSLOG_MAX_MSG_SIZE-1, fmt, ap);
    va_end(ap);

    if (str_len < 0) {
        /* vsnprintf failed */
        return;
    }

    switch (priority) {
    case LOG_EMERG:
    case LOG_ALERT:
    case LOG_CRIT:
    case LOG_ERR:
        logtype = EVENTLOG_ERROR_TYPE;
        break;

    case LOG_WARNING:
        logtype = EVENTLOG_WARNING_TYPE;
        break;

    case LOG_NOTICE:
    case LOG_INFO:
    case LOG_DEBUG:
    default:
        logtype = EVENTLOG_INFORMATION_TYPE;
        break;
    }

    //Windows API suck. They are overengineered
    ReportEventA(ms_eventlog, logtype, 0, 0, NULL, 1, 0,
                 const_cast<const char **>(&str), NULL);
}