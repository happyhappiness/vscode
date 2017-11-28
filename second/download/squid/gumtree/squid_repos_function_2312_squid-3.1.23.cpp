static void
accessLogICAPSquid(AccessLogEntry * al, Logfile * logfile)
{
    const char *client = NULL;
    const char *user = NULL;
    char tmp[MAX_IPSTRLEN], clientbuf[MAX_IPSTRLEN];

    if (al->cache.caddr.IsAnyAddr()) { // ICAP OPTIONS xactions lack client
        client = "-";
    } else {
        if (Config.onoff.log_fqdn)
            client = fqdncache_gethostbyaddr(al->cache.caddr, FQDN_LOOKUP_IF_MISS);
        if (!client)
            client = al->cache.caddr.NtoA(clientbuf, MAX_IPSTRLEN);
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

    logfilePrintf(logfile, "%9ld.%03d %6d %s -/%03d %" PRId64 " %s %s %s -/%s -\n",
                  (long int) current_time.tv_sec,
                  (int) current_time.tv_usec / 1000,

                  al->icap.trTime,
                  client,

                  al->icap.resStatus,
                  al->icap.bytesRead,
                  Adaptation::Icap::ICAP::methodStr(al->icap.reqMethod),
                  al->icap.reqUri.termedBuf(),
                  user ? user : dash_str,
                  al->icap.hostAddr.NtoA(tmp, MAX_IPSTRLEN));
    safe_free(user);
}