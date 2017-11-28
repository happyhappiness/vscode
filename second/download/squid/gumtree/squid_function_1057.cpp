void
Log::Format::HttpdCombined(const AccessLogEntry::Pointer &al, Logfile * logfile)
{
    const char *user_ident = ::Format::QuoteUrlEncodeUsername(al->cache.rfc931);
    const char *user_auth = NULL;
    const char *referer = NULL;
    const char *agent = NULL;

    if (al->request) {
#if USE_AUTH
        if (al->request->auth_user_request != NULL)
            user_auth = ::Format::QuoteUrlEncodeUsername(al->request->auth_user_request->username());
#endif
        referer = al->request->header.getStr(HDR_REFERER);
        agent = al->request->header.getStr(HDR_USER_AGENT);
    }

    if (!referer || *referer == '\0')
        referer = "-";

    if (!agent || *agent == '\0')
        agent = "-";

    char clientip[MAX_IPSTRLEN];
    al->getLogClientIp(clientip, MAX_IPSTRLEN);

    logfilePrintf(logfile, "%s %s %s [%s] \"%s %s %s/%d.%d\" %d %" PRId64 " \"%s\" \"%s\" %s%s:%s%s",
                  clientip,
                  user_ident ? user_ident : dash_str,
                  user_auth ? user_auth : dash_str,
                  Time::FormatHttpd(squid_curtime),
                  al->_private.method_str,
                  al->url,
                  AnyP::ProtocolType_str[al->http.version.protocol],
                  al->http.version.major, al->http.version.minor,
                  al->http.code,
                  al->cache.replySize,
                  referer,
                  agent,
                  LogTags_str[al->cache.code],
                  al->http.statusSfx(),
                  hier_code_str[al->hier.code],
                  (Config.onoff.log_mime_hdrs?"":"\n"));

    safe_free(user_ident);
    safe_free(user_auth);

    if (Config.onoff.log_mime_hdrs) {
        char *ereq = ::Format::QuoteMimeBlob(al->headers.request);
        char *erep = ::Format::QuoteMimeBlob(al->headers.reply);
        logfilePrintf(logfile, " [%s] [%s]\n", ereq, erep);
        safe_free(ereq);
        safe_free(erep);
    }
}