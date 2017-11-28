#endif
    const char *user_ident = ::Format::QuoteUrlEncodeUsername(al->cache.rfc931);

    char clientip[MAX_IPSTRLEN];
    al->getLogClientIp(clientip, MAX_IPSTRLEN);

    static SBuf method;
    if (al->_private.method_str)
        method.assign(al->_private.method_str);
    else
        method = al->http.method.image();

    logfilePrintf(logfile, "%s %s %s [%s] \"" SQUIDSBUFPH " %s %s/%d.%d\" %d %" PRId64 " %s%s:%s%s",
                  clientip,
                  user_ident ? user_ident : dash_str,
                  user_auth ? user_auth : dash_str,
                  Time::FormatHttpd(squid_curtime),
                  SQUIDSBUFPRINT(method),
                  al->url,
                  AnyP::ProtocolType_str[al->http.version.protocol],
                  al->http.version.major, al->http.version.minor,
                  al->http.code,
                  al->http.clientReplySz.messageTotal(),
                  LogTags_str[al->cache.code],
                  al->http.statusSfx(),
                  hier_code_str[al->hier.code],
                  (Config.onoff.log_mime_hdrs?"":"\n"));

    safe_free(user_auth);
