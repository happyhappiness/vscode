static int syslog_ntoa (const char* s)
{
#define syslog_symbol(a) #a, a
    static syslog_symbol_t _symbols[] = {
        { syslog_symbol(LOG_AUTHPRIV) },
        { syslog_symbol(LOG_DAEMON) },
        { syslog_symbol(LOG_LOCAL0) },
        { syslog_symbol(LOG_LOCAL1) },
        { syslog_symbol(LOG_LOCAL2) },
        { syslog_symbol(LOG_LOCAL3) },
        { syslog_symbol(LOG_LOCAL4) },
        { syslog_symbol(LOG_LOCAL5) },
        { syslog_symbol(LOG_LOCAL6) },
        { syslog_symbol(LOG_LOCAL7) },
        { syslog_symbol(LOG_USER) },
        { syslog_symbol(LOG_ERR) },
        { syslog_symbol(LOG_WARNING) },
        { syslog_symbol(LOG_NOTICE) },
        { syslog_symbol(LOG_INFO) },
        { syslog_symbol(LOG_DEBUG) },
        { NULL, 0 }
    };

    for (syslog_symbol_t* p = _symbols; p->name != NULL; ++p)
        if (!strcmp(s, p->name) || !strcasecmp(s, p->name+4))
            return p->value;

    debugs(1, 1, "Unknown syslog facility/priority '" << s << "'");

    return 0;
}