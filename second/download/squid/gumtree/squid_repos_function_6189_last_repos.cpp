void
Log::Format::SquidNative(const AccessLogEntry::Pointer &al, Logfile * logfile)
{
    char hierHost[MAX_IPSTRLEN];

    const char *user = NULL;

#if USE_AUTH
    if (al->request && al->request->auth_user_request != NULL)
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

    char clientip[MAX_IPSTRLEN];
    al->getLogClientIp(clientip, MAX_IPSTRLEN);

    const SBuf method(al->getLogMethod());

    logfilePrintf(logfile, "%9ld.%03d %6ld %s %s/%03d %" PRId64 " " SQUIDSBUFPH " " SQUIDSBUFPH " %s %s%s/%s %s%s",
                  (long int) current_time.tv_sec,
                  (int) current_time.tv_usec / 1000,
                  tvToMsec(al->cache.trTime),
                  clientip,
                  al->cache.code.c_str(),
                  al->http.code,
                  al->http.clientReplySz.messageTotal(),
                  SQUIDSBUFPRINT(method),
                  SQUIDSBUFPRINT(al->url),
                  user ? user : dash_str,
                  al->hier.ping.timedout ? "TIMEOUT_" : "",
                  hier_code_str[al->hier.code],
                  al->hier.tcpServer != NULL ? al->hier.tcpServer->remote.toStr(hierHost, sizeof(hierHost)) : "-",
                  al->http.content_type,
                  (Config.onoff.log_mime_hdrs?"":"\n"));

    safe_free(user);

    if (Config.onoff.log_mime_hdrs) {
        char *ereq = ::Format::QuoteMimeBlob(al->headers.request);
        char *erep = ::Format::QuoteMimeBlob(al->headers.reply);
        logfilePrintf(logfile, " [%s] [%s]\n", ereq, erep);
        safe_free(ereq);
        safe_free(erep);
    }
}