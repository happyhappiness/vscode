void
accessLogDumpLogFormat(StoreEntry * entry, const char *name, logformat * definitions)
{
    logformat_token *t;
    logformat *format;

    struct logformat_token_table_entry *te;
    debugs(46, 4, "accessLogDumpLogFormat called");

    for (format = definitions; format; format = format->next) {
        debugs(46, 3, "Dumping logformat definition for " << format->name);
        storeAppendPrintf(entry, "logformat %s ", format->name);

        for (t = format->format; t; t = t->next) {
            if (t->type == LFT_STRING)
                storeAppendPrintf(entry, "%s", t->data.string);
            else {
                char argbuf[256];
                char *arg = NULL;
                logformat_bcode_t type = t->type;

                switch (type) {
                    /* special cases */

                case LFT_STRING:
                    break;
#if ICAP_CLIENT
                case LFT_ICAP_LAST_MATCHED_HEADER_ELEM:
                case LFT_ICAP_REQ_HEADER_ELEM:
                case LFT_ICAP_REP_HEADER_ELEM:
#endif
                case LFT_REQUEST_HEADER_ELEM:
                case LFT_ADAPTED_REQUEST_HEADER_ELEM:
                case LFT_REPLY_HEADER_ELEM:

                    if (t->data.header.separator != ',')
                        snprintf(argbuf, sizeof(argbuf), "%s:%c%s", t->data.header.header, t->data.header.separator, t->data.header.element);
                    else
                        snprintf(argbuf, sizeof(argbuf), "%s:%s", t->data.header.header, t->data.header.element);

                    arg = argbuf;

                    switch (type) {
                    case LFT_REQUEST_HEADER_ELEM:
                        type = LFT_REQUEST_HEADER_ELEM;
                        break;
                    case LFT_ADAPTED_REQUEST_HEADER_ELEM:
                        type = LFT_ADAPTED_REQUEST_HEADER_ELEM;
                        break;
                    case LFT_REPLY_HEADER_ELEM:
                        type = LFT_REPLY_HEADER_ELEM;
                        break;
#if ICAP_CLIENT
                    case LFT_ICAP_LAST_MATCHED_HEADER_ELEM:
                        type = LFT_ICAP_LAST_MATCHED_HEADER;
                        break;
                    case LFT_ICAP_REQ_HEADER_ELEM:
                        type = LFT_ICAP_REQ_HEADER;
                        break;
                    case LFT_ICAP_REP_HEADER_ELEM:
                        type = LFT_ICAP_REP_HEADER;
                        break;
#endif
                    default:
                        break;
                    }

                    break;

                case LFT_REQUEST_ALL_HEADERS:
                case LFT_ADAPTED_REQUEST_ALL_HEADERS:
                case LFT_REPLY_ALL_HEADERS:

#if ICAP_CLIENT
                case LFT_ICAP_LAST_MATCHED_ALL_HEADERS:
                case LFT_ICAP_REQ_ALL_HEADERS:
                case LFT_ICAP_REP_ALL_HEADERS:
#endif

                    switch (type) {
                    case LFT_REQUEST_ALL_HEADERS:
                        type = LFT_REQUEST_HEADER;
                        break;
                    case LFT_ADAPTED_REQUEST_ALL_HEADERS:
                        type = LFT_ADAPTED_REQUEST_HEADER;
                        break;
                    case LFT_REPLY_ALL_HEADERS:
                        type = LFT_REPLY_HEADER;
                        break;
#if ICAP_CLIENT
                    case LFT_ICAP_LAST_MATCHED_ALL_HEADERS:
                        type = LFT_ICAP_LAST_MATCHED_HEADER;
                        break;
                    case LFT_ICAP_REQ_ALL_HEADERS:
                        type = LFT_ICAP_REQ_HEADER;
                        break;
                    case LFT_ICAP_REP_ALL_HEADERS:
                        type = LFT_ICAP_REP_HEADER;
                        break;
#endif
                    default:
                        break;
                    }

                    break;

                default:
                    if (t->data.string)
                        arg = t->data.string;

                    break;
                }

                entry->append("%", 1);

                switch (t->quote) {

                case LOG_QUOTE_QUOTES:
                    entry->append("\"", 1);
                    break;

                case LOG_QUOTE_BRAKETS:
                    entry->append("[", 1);
                    break;

                case LOG_QUOTE_URL:
                    entry->append("#", 1);
                    break;

                case LOG_QUOTE_RAW:
                    entry->append("'", 1);
                    break;

                case LOG_QUOTE_NONE:
                    break;
                }

                if (t->left)
                    entry->append("-", 1);

                if (t->zero)
                    entry->append("0", 1);

                if (t->width)
                    storeAppendPrintf(entry, "%d", (int) t->width);

                if (t->precision)
                    storeAppendPrintf(entry, ".%d", (int) t->precision);

                if (arg)
                    storeAppendPrintf(entry, "{%s}", arg);

                for (te = logformat_token_table; te->config != NULL; te++) {
                    if (te->token_type == type) {
                        storeAppendPrintf(entry, "%s", te->config);
                        break;
                    }
                }

                if (t->space)
                    entry->append(" ", 1);

                assert(te->config != NULL);
            }
        }

        entry->append("\n", 1);
    }

}