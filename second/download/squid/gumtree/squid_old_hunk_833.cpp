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
