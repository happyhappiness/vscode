int
Format::Token::parse(const char *def, Quoting *quoting)
{
    const char *cur = def;

    int l;

    l = strcspn(cur, "%");

    if (l > 0) {
        char *cp;
        /* it's a string for sure, until \0 or the next % */
        cp = (char *)xmalloc(l + 1);
        xstrncpy(cp, cur, l + 1);
        type = LFT_STRING;
        data.string = cp;

        while (l > 0) {
            switch (*cur) {

            case '"':

                if (*quoting == LOG_QUOTE_NONE)
                    *quoting = LOG_QUOTE_QUOTES;
                else if (*quoting == LOG_QUOTE_QUOTES)
                    *quoting = LOG_QUOTE_NONE;

                break;

            case '[':
                if (*quoting == LOG_QUOTE_NONE)
                    *quoting = LOG_QUOTE_MIMEBLOB;

                break;

            case ']':
                if (*quoting == LOG_QUOTE_MIMEBLOB)
                    *quoting = LOG_QUOTE_NONE;

                break;
            }

            ++cur;
            --l;
        }

        goto done;
    }

    if (!*cur)
        goto done;

    ++cur;

    // select quoting style for his particular token
    switch (*cur) {

    case '"':
        quote = LOG_QUOTE_QUOTES;
        ++cur;
        break;

    case '\'':
        quote = LOG_QUOTE_RAW;
        ++cur;
        break;

    case '[':
        quote = LOG_QUOTE_MIMEBLOB;
        ++cur;
        break;

    case '#':
        quote = LOG_QUOTE_URL;
        ++cur;
        break;

    default:
        quote = *quoting;
        break;
    }

    if (*cur == '-') {
        left = 1;
        ++cur;
    }

    if (*cur == '0') {
        zero = 1;
        ++cur;
    }

    char *endp;
    if (xisdigit(*cur)) {
        widthMin = strtol(cur, &endp, 10);
        cur = endp;
    }

    if (*cur == '.' && xisdigit(*(++cur))) {
        widthMax = strtol(cur, &endp, 10);
        cur = endp;
    }

    if (*cur == '{') {
        char *cp;
        ++cur;
        l = strcspn(cur, "}");
        cp = (char *)xmalloc(l + 1);
        xstrncpy(cp, cur, l + 1);
        data.string = cp;
        cur += l;

        if (*cur == '}')
            ++cur;
    }

    type = LFT_NONE;

    // Scan each registered token namespace
    debugs(46, 9, HERE << "check for token in " << TheConfig.tokens.size() << " namespaces.");
    for (std::list<TokenNamespace>::const_iterator itr = TheConfig.tokens.begin(); itr != TheConfig.tokens.end(); ++itr) {
        debugs(46, 7, HERE << "check for possible " << itr->prefix << ":: token");
        const size_t len = itr->prefix.size();
        if (itr->prefix.cmp(cur, len) == 0 && cur[len] == ':' && cur[len+1] == ':') {
            debugs(46, 5, HERE << "check for " << itr->prefix << ":: token in '" << cur << "'");
            const char *old = cur;
            cur = scanForToken(itr->tokenSet, cur+len+2);
            if (old != cur) // found
                break;
            else // reset to start of namespace
                cur = cur - len - 2;
        }
    }

    if (type == LFT_NONE) {
        // For upward compatibility, assume "http::" prefix as default prefix
        // for all log access formatting codes, except those starting with a
        // "%" or a known namespace. (ie "icap::", "adapt::")
        if (strncmp(cur,"http::", 6) == 0 && *(cur+6) != '%' )
            cur += 6;

        // NP: scan the sets of tokens in decreasing size to guarantee no
        //     mistakes made with overlapping names. (Bug 3310)

        // Scan for various long tokens
        debugs(46, 5, HERE << "scan for possible Misc token");
        cur = scanForToken(TokenTableMisc, cur);
        // scan for 2-char tokens
        if (type == LFT_NONE) {
            debugs(46, 5, HERE << "scan for possible 2C token");
            cur = scanForToken(TokenTable2C, cur);
        }
        // finally scan for 1-char tokens.
        if (type == LFT_NONE) {
            debugs(46, 5, HERE << "scan for possible 1C token");
            cur = scanForToken(TokenTable1C, cur);
        }
    }

    if (type == LFT_NONE) {
        fatalf("Can't parse configuration token: '%s'\n", def);
    }

    if (*cur == ' ') {
        space = 1;
        ++cur;
    }

done:

    switch (type) {

#if USE_ADAPTATION
    case LFT_ADAPTATION_LAST_HEADER:
#endif

#if ICAP_CLIENT
    case LFT_ICAP_REQ_HEADER:

    case LFT_ICAP_REP_HEADER:
#endif

    case LFT_ADAPTED_REQUEST_HEADER:

    case LFT_REQUEST_HEADER:

    case LFT_REPLY_HEADER:

        if (data.string) {
            char *header = data.string;
            char *cp = strchr(header, ':');

            if (cp) {
                *cp = '\0';
                ++cp;

                if (*cp == ',' || *cp == ';' || *cp == ':') {
                    data.header.separator = *cp;
                    ++cp;
                } else {
                    data.header.separator = ',';
                }

                data.header.element = cp;

                switch (type) {
                case LFT_REQUEST_HEADER:
                    type = LFT_REQUEST_HEADER_ELEM;
                    break;

                case LFT_ADAPTED_REQUEST_HEADER:
                    type = LFT_ADAPTED_REQUEST_HEADER_ELEM;
                    break;

                case LFT_REPLY_HEADER:
                    type = LFT_REPLY_HEADER_ELEM;
                    break;
#if USE_ADAPTATION
                case LFT_ADAPTATION_LAST_HEADER:
                    type = LFT_ADAPTATION_LAST_HEADER_ELEM;
                    break;
#endif
#if ICAP_CLIENT
                case LFT_ICAP_REQ_HEADER:
                    type = LFT_ICAP_REQ_HEADER_ELEM;
                    break;
                case LFT_ICAP_REP_HEADER:
                    type = LFT_ICAP_REP_HEADER_ELEM;
                    break;
#endif
                default:
                    break;
                }
            }

            data.header.header = header;
        } else {
            switch (type) {
            case LFT_REQUEST_HEADER:
                type = LFT_REQUEST_ALL_HEADERS;
                break;

            case LFT_ADAPTED_REQUEST_HEADER:
                type = LFT_ADAPTED_REQUEST_ALL_HEADERS;
                break;

            case LFT_REPLY_HEADER:
                type = LFT_REPLY_ALL_HEADERS;
                break;
#if USE_ADAPTATION
            case LFT_ADAPTATION_LAST_HEADER:
                type = LFT_ADAPTATION_LAST_ALL_HEADERS;
                break;
#endif
#if ICAP_CLIENT
            case LFT_ICAP_REQ_HEADER:
                type = LFT_ICAP_REQ_ALL_HEADERS;
                break;
            case LFT_ICAP_REP_HEADER:
                type = LFT_ICAP_REP_ALL_HEADERS;
                break;
#endif
            default:
                break;
            }
            Config.onoff.log_mime_hdrs = 1;
        }

        break;

    case LFT_CLIENT_FQDN:
        Config.onoff.log_fqdn = 1;
        break;

    case LFT_TIME_SUBSECOND:
        divisor = 1000;

        if (widthMax > 0) {
            int i;
            divisor = 1000000;

            for (i = widthMax; i > 1; --i)
                divisor /= 10;

            if (!divisor)
                divisor = 0;
        }
        break;

    case LFT_HTTP_SENT_STATUS_CODE_OLD_30:
        debugs(46, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: The \"Hs\" formatting code is deprecated. Use the \">Hs\" instead.");
        type = LFT_HTTP_SENT_STATUS_CODE;
        break;

    case LFT_SERVER_LOCAL_IP_OLD_27:
        debugs(46, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: The \"oa\" formatting code is deprecated. Use the \"<la\" instead.");
        type = LFT_SERVER_LOCAL_IP;
        break;

    case LFT_REQUEST_URLPATH_OLD_31:
        debugs(46, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: The \"rp\" formatting code is deprecated. Use the \">rp\" instead.");
        type = LFT_CLIENT_REQ_URLPATH;
        break;

    case LFT_REQUEST_VERSION_OLD_2X:
        debugs(46, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: The \">v\" formatting code is deprecated. Use the \">rv\" instead.");
        type = LFT_REQUEST_VERSION;
        break;

#if !USE_SQUID_EUI
    case LFT_CLIENT_EUI:
        debugs(46, DBG_CRITICAL, "WARNING: The \">eui\" formatting code requires EUI features which are disabled in this Squid.");
        break;
#endif

    default:
        break;
    }

    return (cur - def);
}