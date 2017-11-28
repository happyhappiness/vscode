void
Log::Format::SquidIcap(const AccessLogEntry::Pointer &al, Logfile * logfile)
{
    const char *client = NULL;
    const char *user = NULL;
    char tmp[MAX_IPSTRLEN], clientbuf[MAX_IPSTRLEN];

    if (al->cache.caddr.isAnyAddr()) { // ICAP OPTIONS xactions lack client
        client = "-";
    } else {
        if (Config.onoff.log_fqdn)
            client = fqdncache_gethostbyaddr(al->cache.caddr, FQDN_LOOKUP_IF_MISS);
        if (!client)
            client = al->cache.caddr.toStr(clientbuf, MAX_IPSTRLEN);
    }

#if USE_AUTH
    if (al->request != NULL && al->request->auth_user_request != NULL)
        user = ::Format::QuoteUrlEncodeUsername(al->request->auth_user_request->username());
#endif

    if (!user)
        user = ::Format::QuoteUrlEncodeUsername(al->cache.extuser);

#if USE_OPENSSL
    if (!user)
        user = ::Format::QuoteUrlEncodeUsername(al->cache.ssluser);
#endif

    if (!user)
        user = ::Format::QuoteUrlEncodeUsername(al->cache.rfc931);

    if (user && !*user)
        safe_free(user);

    logfilePrintf(logfile, "%9ld.%03d %6ld %s %s/%03d %" PRId64 " %s %s %s -/%s -\n",
                  (long int) current_time.tv_sec,
                  (int) current_time.tv_usec / 1000,
                  tvToMsec(al->icap.trTime),
                  client,
                  al->icap.outcome,
                  al->icap.resStatus,
                  al->icap.bytesRead,
                  Adaptation::Icap::ICAP::methodStr(al->icap.reqMethod),
                  al->icap.reqUri.termedBuf(),
                  user ? user : "-",
                  al->icap.hostAddr.toStr(tmp, MAX_IPSTRLEN));
    safe_free(user);
}