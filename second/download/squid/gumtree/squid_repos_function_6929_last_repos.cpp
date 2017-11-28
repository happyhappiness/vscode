void
Format::Format::dump(StoreEntry * entry, const char *directiveName, bool eol) const
{
    debugs(46, 4, HERE);

    // loop rather than recursing to conserve stack space.
    for (const Format *fmt = this; fmt; fmt = fmt->next) {
        debugs(46, 3, HERE << "Dumping format definition for " << fmt->name);
        if (directiveName)
            storeAppendPrintf(entry, "%s %s ", directiveName, fmt->name);

        for (Token *t = fmt->format; t; t = t->next) {
            if (t->type == LFT_STRING)
                storeAppendPrintf(entry, "%s", t->data.string);
            else {
                char argbuf[256];
                char *arg = NULL;
                ByteCode_t type = t->type;

                switch (type) {
                /* special cases */

                case LFT_STRING:
                    break;
#if USE_ADAPTATION
                case LFT_ADAPTATION_LAST_HEADER_ELEM:
#endif
#if ICAP_CLIENT
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
                        type = LFT_REQUEST_HEADER_ELEM; // XXX: remove _ELEM?
                        break;
                    case LFT_ADAPTED_REQUEST_HEADER_ELEM:
                        type = LFT_ADAPTED_REQUEST_HEADER_ELEM; // XXX: remove _ELEM?
                        break;
                    case LFT_REPLY_HEADER_ELEM:
                        type = LFT_REPLY_HEADER_ELEM; // XXX: remove _ELEM?
                        break;
#if USE_ADAPTATION
                    case LFT_ADAPTATION_LAST_HEADER_ELEM:
                        type = LFT_ADAPTATION_LAST_HEADER;
                        break;
#endif
#if ICAP_CLIENT
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

#if USE_ADAPTATION
                case LFT_ADAPTATION_LAST_ALL_HEADERS:
#endif
#if ICAP_CLIENT
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
#if USE_ADAPTATION
                    case LFT_ADAPTATION_LAST_ALL_HEADERS:
                        type = LFT_ADAPTATION_LAST_HEADER;
                        break;
#endif
#if ICAP_CLIENT
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

                case LOG_QUOTE_MIMEBLOB:
                    entry->append("[", 1);
                    break;

                case LOG_QUOTE_URL:
                    entry->append("#", 1);
                    break;

                case LOG_QUOTE_RAW:
                    entry->append("'", 1);
                    break;

                case LOG_QUOTE_SHELL:
                    entry->append("/", 1);
                    break;

                case LOG_QUOTE_NONE:
                    break;
                }

                if (t->left)
                    entry->append("-", 1);

                if (t->zero)
                    entry->append("0", 1);

                if (t->widthMin >= 0)
                    storeAppendPrintf(entry, "%d", t->widthMin);

                if (t->widthMax >= 0)
                    storeAppendPrintf(entry, ".%d", t->widthMax);

                if (arg)
                    storeAppendPrintf(entry, "{%s}", arg);

                storeAppendPrintf(entry, "%s", t->label);

                if (t->space)
                    entry->append(" ", 1);
            }
        }

        if (eol)
            entry->append("\n", 1);
    }

}