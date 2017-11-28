void
logReferer(const char *client, const char *referer, const char *uri)
{
#if USE_REFERER_LOG

    if (NULL == refererlog)
        return;

    logfilePrintf(refererlog, "%9d.%03d %s %s %s\n",
                  (int) current_time.tv_sec,
                  (int) current_time.tv_usec / 1000,
                  client,
                  referer,
                  uri ? uri : "-");

#endif
}