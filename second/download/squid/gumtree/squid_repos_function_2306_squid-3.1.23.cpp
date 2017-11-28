static int
accessLogGetNewLogFormatToken(logformat_token * lt, char *def, enum log_quote *quote)
{
    char *cur = def;

    struct logformat_token_table_entry *lte;
    int l;

    memset(lt, 0, sizeof(*lt));
    l = strcspn(cur, "%");

    if (l > 0) {
        char *cp;
        /* it's a string for sure, until \0 or the next % */
        cp = (char *)xmalloc(l + 1);
        xstrncpy(cp, cur, l + 1);
        lt->type = LFT_STRING;
        lt->data.string = cp;

        while (l > 0) {
            switch (*cur) {

            case '"':

                if (*quote == LOG_QUOTE_NONE)
                    *quote = LOG_QUOTE_QUOTES;
                else if (*quote == LOG_QUOTE_QUOTES)
                    *quote = LOG_QUOTE_NONE;

                break;

            case '[':
                if (*quote == LOG_QUOTE_NONE)
                    *quote = LOG_QUOTE_BRAKETS;

                break;

            case ']':
                if (*quote == LOG_QUOTE_BRAKETS)
                    *quote = LOG_QUOTE_NONE;

                break;
            }

            cur++;
            l--;
        }

        goto done;
    }

    if (!*cur)
        goto done;

    cur++;

    switch (*cur) {

    case '"':
        lt->quote = LOG_QUOTE_QUOTES;
        cur++;
        break;

    case '\'':
        lt->quote = LOG_QUOTE_RAW;
        cur++;
        break;

    case '[':
        lt->quote = LOG_QUOTE_BRAKETS;
        cur++;
        break;

    case '#':
        lt->quote = LOG_QUOTE_URL;
        cur++;
        break;

    default:
        lt->quote = *quote;
        break;
    }

    if (*cur == '-') {
        lt->left = 1;
        cur++;
    }

    if (*cur == '0') {
        lt->zero = 1;
        cur++;
    }

    if (xisdigit(*cur))
        lt->width = strtol(cur, &cur, 10);

    if (*cur == '.')
        lt->precision = strtol(cur + 1, &cur, 10);

    if (*cur == '{') {
        char *cp;
        cur++;
        l = strcspn(cur, "}");
        cp = (char *)xmalloc(l + 1);
        xstrncpy(cp, cur, l + 1);
        lt->data.string = cp;
        cur += l;

        if (*cur == '}')
            cur++;
    }

    // For upward compatibility, assume "http::" prefix as default prefix
    // for all log access formating codes, except those starting
    // from "icap::", "adapt::" and "%"
    if (strncmp(cur,"http::", 6) == 0 &&
            strncmp(cur+6, "icap::", 6) != 0  &&
            strncmp(cur+6, "adapt::", 12) != 0 && *(cur+6) != '%' ) {
        cur += 6;
    }

    lt->type = LFT_NONE;

    for (lte = logformat_token_table; lte->config != NULL; lte++) {
        if (strncmp(lte->config, cur, strlen(lte->config)) == 0) {
            lt->type = lte->token_type;
            cur += strlen(lte->config);
            break;
        }
    }

    if (lt->type == LFT_NONE) {
        fatalf("Can't parse configuration token: '%s'\n",
               def);
    }

    if (*cur == ' ') {
        lt->space = 1;
        cur++;
    }

done:

    switch (lt->type) {

#if ICAP_CLIENT
    case LFT_ICAP_LAST_MATCHED_HEADER:

    case LFT_ICAP_REQ_HEADER:

    case LFT_ICAP_REP_HEADER:
#endif

    case LFT_ADAPTED_REQUEST_HEADER:

    case LFT_REQUEST_HEADER:

    case LFT_REPLY_HEADER:

        if (lt->data.string) {
            char *header = lt->data.string;
            char *cp = strchr(header, ':');

            if (cp) {
                *cp++ = '\0';

                if (*cp == ',' || *cp == ';' || *cp == ':')
                    lt->data.header.separator = *cp++;
                else
                    lt->data.header.separator = ',';

                lt->data.header.element = cp;

                switch (lt->type) {
                case LFT_REQUEST_HEADER:
                    lt->type = LFT_REQUEST_HEADER_ELEM;
                    break;

                case LFT_ADAPTED_REQUEST_HEADER:
                    lt->type = LFT_ADAPTED_REQUEST_HEADER_ELEM;
                    break;

                case LFT_REPLY_HEADER:
                    lt->type = LFT_REPLY_HEADER_ELEM;
                    break;
#if ICAP_CLIENT
                case LFT_ICAP_LAST_MATCHED_HEADER:
                    lt->type = LFT_ICAP_LAST_MATCHED_HEADER_ELEM;
                    break;
                case LFT_ICAP_REQ_HEADER:
                    lt->type = LFT_ICAP_REQ_HEADER_ELEM;
                    break;
                case LFT_ICAP_REP_HEADER:
                    lt->type = LFT_ICAP_REP_HEADER_ELEM;
                    break;
#endif
                default:
                    break;
                }
            }

            lt->data.header.header = header;
        } else {
            switch (lt->type) {
            case LFT_REQUEST_HEADER:
                lt->type = LFT_REQUEST_ALL_HEADERS;
                break;

            case LFT_ADAPTED_REQUEST_HEADER:
                lt->type = LFT_ADAPTED_REQUEST_ALL_HEADERS;
                break;

            case LFT_REPLY_HEADER:
                lt->type = LFT_REPLY_ALL_HEADERS;
                break;
#if ICAP_CLIENT
            case LFT_ICAP_LAST_MATCHED_HEADER:
                lt->type = LFT_ICAP_LAST_MATCHED_ALL_HEADERS;
                break;
            case LFT_ICAP_REQ_HEADER:
                lt->type = LFT_ICAP_REQ_ALL_HEADERS;
                break;
            case LFT_ICAP_REP_HEADER:
                lt->type = LFT_ICAP_REP_ALL_HEADERS;
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
        lt->divisor = 1000;

        if (lt->precision) {
            int i;
            lt->divisor = 1000000;

            for (i = lt->precision; i > 1; i--)
                lt->divisor /= 10;

            if (!lt->divisor)
                lt->divisor = 0;
        }

        break;

    case LFT_HTTP_SENT_STATUS_CODE_OLD_30:
        debugs(46, 0, "WARNING: the \"Hs\" formating code is deprecated use the \">Hs\" instead");
        lt->type = LFT_HTTP_SENT_STATUS_CODE;
        break;

    case LFT_PEER_LOCAL_IP_OLD_27:
        debugs(46, 0, "WARNING: The \"oa\" formatting code is deprecated. Use the \"<la\" instead.");
        lt->type = LFT_PEER_LOCAL_IP;
        break;

    default:
        break;
    }

    return (cur - def);
}