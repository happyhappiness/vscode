
    if (al->request) {
#if USE_AUTH
        if (al->request->auth_user_request != NULL)
            user_auth = ::Format::QuoteUrlEncodeUsername(al->request->auth_user_request->username());
#endif
        referer = al->request->header.getStr(Http::HdrType::REFERER);
        agent = al->request->header.getStr(Http::HdrType::USER_AGENT);
    }

    if (!referer || *referer == '\0')
        referer = "-";

    if (!agent || *agent == '\0')
        agent = "-";

    char clientip[MAX_IPSTRLEN];
    al->getLogClientIp(clientip, MAX_IPSTRLEN);

    const SBuf method(al->getLogMethod());

    logfilePrintf(logfile, "%s %s %s [%s] \"" SQUIDSBUFPH " " SQUIDSBUFPH " %s/%d.%d\" %d %" PRId64 " \"%s\" \"%s\" %s:%s%s",
                  clientip,
                  user_ident ? user_ident : dash_str,
                  user_auth ? user_auth : dash_str,
                  Time::FormatHttpd(squid_curtime),
                  SQUIDSBUFPRINT(method),
                  SQUIDSBUFPRINT(al->url),
                  AnyP::ProtocolType_str[al->http.version.protocol],
                  al->http.version.major, al->http.version.minor,
                  al->http.code,
                  al->http.clientReplySz.messageTotal(),
                  referer,
                  agent,
                  al->cache.code.c_str(),
                  hier_code_str[al->hier.code],
                  (Config.onoff.log_mime_hdrs?"":"\n"));

    safe_free(user_ident);
    safe_free(user_auth);

