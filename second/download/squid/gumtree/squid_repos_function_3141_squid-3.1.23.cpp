void
logUserAgent(const char *client, const char *agent)
{
#if USE_USERAGENT_LOG
    static time_t last_time = 0;
    static char time_str[128];
    const char *s;

    if (NULL == useragentlog)
        return;

    if (squid_curtime != last_time) {
        s = mkhttpdlogtime(&squid_curtime);
        strcpy(time_str, s);
        last_time = squid_curtime;
    }

    logfilePrintf(useragentlog, "%s [%s] \"%s\"\n",
                  client,
                  time_str,
                  agent);
#endif
}