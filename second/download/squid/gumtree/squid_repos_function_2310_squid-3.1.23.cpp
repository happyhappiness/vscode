static void
accessLogSquid(AccessLogEntry * al, Logfile * logfile)
{
    const char *client = NULL;
    const char *user = NULL;
    char buf[MAX_IPSTRLEN];

    if (Config.onoff.log_fqdn) {
        client = fqdncache_gethostbyaddr(al->cache.caddr, FQDN_LOOKUP_IF_MISS);
    }

    if (client == NULL) {
        client = al->cache.caddr.NtoA(buf,MAX_IPSTRLEN);
    }

    user = accessLogFormatName(al->cache.authuser);

    if (!user)
        user = accessLogFormatName(al->cache.extuser);

#if USE_SSL

    if (!user)
        user = accessLogFormatName(al->cache.ssluser);

#endif

    if (!user)
        user = accessLogFormatName(al->cache.rfc931);

    if (user && !*user)
        safe_free(user);

    if (!Config.onoff.log_mime_hdrs) {
        logfilePrintf(logfile, "%9ld.%03d %6d %s %s/%03d %" PRId64 " %s %s %s %s%s/%s %s\n",
                      (long int) current_time.tv_sec,
                      (int) current_time.tv_usec / 1000,
                      al->cache.msec,
                      client,
                      log_tags[al->cache.code],
                      al->http.code,
                      al->cache.replySize,
                      al->_private.method_str,
                      al->url,
                      user ? user : dash_str,
                      al->hier.ping.timedout ? "TIMEOUT_" : "",
                      hier_strings[al->hier.code],
                      al->hier.host,
                      al->http.content_type);
    } else {
        char *ereq = log_quote(al->headers.request);
        char *erep = log_quote(al->headers.reply);
        logfilePrintf(logfile, "%9ld.%03d %6d %s %s/%03d %" PRId64 " %s %s %s %s%s/%s %s [%s] [%s]\n",
                      (long int) current_time.tv_sec,
                      (int) current_time.tv_usec / 1000,
                      al->cache.msec,
                      client,
                      log_tags[al->cache.code],
                      al->http.code,
                      al->cache.replySize,
                      al->_private.method_str,
                      al->url,
                      user ? user : dash_str,
                      al->hier.ping.timedout ? "TIMEOUT_" : "",
                      hier_strings[al->hier.code],
                      al->hier.host,
                      al->http.content_type,
                      ereq,
                      erep);
        safe_free(ereq);
        safe_free(erep);
    }
    safe_free(user);
}