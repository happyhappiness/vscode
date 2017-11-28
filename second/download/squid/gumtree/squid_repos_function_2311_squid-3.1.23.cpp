static void
accessLogCommon(AccessLogEntry * al, Logfile * logfile)
{
    const char *client = NULL;
    char *user1 = NULL, *user2 = NULL;
    char buf[MAX_IPSTRLEN];

    if (Config.onoff.log_fqdn) {
        client = fqdncache_gethostbyaddr(al->cache.caddr, 0);
    }

    if (client == NULL) {
        client = al->cache.caddr.NtoA(buf,MAX_IPSTRLEN);
    }

    user1 = accessLogFormatName(al->cache.authuser);

    user2 = accessLogFormatName(al->cache.rfc931);

    logfilePrintf(logfile, "%s %s %s [%s] \"%s %s HTTP/%d.%d\" %d %" PRId64 " %s:%s%s",
                  client,
                  user2 ? user2 : dash_str,
                  user1 ? user1 : dash_str,
                  mkhttpdlogtime(&squid_curtime),
                  al->_private.method_str,
                  al->url,
                  al->http.version.major, al->http.version.minor,
                  al->http.code,
                  al->cache.replySize,
                  log_tags[al->cache.code],
                  hier_strings[al->hier.code],
                  (Config.onoff.log_mime_hdrs?"":"\n"));

    safe_free(user1);

    safe_free(user2);

    if (Config.onoff.log_mime_hdrs) {
        char *ereq = log_quote(al->headers.request);
        char *erep = log_quote(al->headers.reply);
        logfilePrintf(logfile, " [%s] [%s]\n", ereq, erep);
        safe_free(ereq);
        safe_free(erep);
    }
}