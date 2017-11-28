void
accessLogLogTo(CustomLog* log, AccessLogEntry::Pointer &al, ACLChecklist * checklist)
{

    if (al->url == NULL)
        al->url = dash_str;

    if (!al->http.content_type || *al->http.content_type == '\0')
        al->http.content_type = dash_str;

    if (al->icp.opcode)
        al->_private.method_str = icp_opcode_str[al->icp.opcode];
    else if (al->htcp.opcode)
        al->_private.method_str = al->htcp.opcode;
    else
        al->_private.method_str = RequestMethodStr(al->http.method);

    if (al->hier.host[0] == '\0')
        xstrncpy(al->hier.host, dash_str, SQUIDHOSTNAMELEN);

    for (; log; log = log->next) {
        if (log->aclList && checklist && checklist->fastCheck(log->aclList) != ACCESS_ALLOWED)
            continue;

        // The special-case "none" type has no logfile object set
        if (log->type == Log::Format::CLF_NONE)
            return;

        if (log->logfile) {
            logfileLineStart(log->logfile);

            switch (log->type) {

            case Log::Format::CLF_SQUID:
                Log::Format::SquidNative(al, log->logfile);
                break;

            case Log::Format::CLF_COMBINED:
                Log::Format::HttpdCombined(al, log->logfile);
                break;

            case Log::Format::CLF_COMMON:
                Log::Format::HttpdCommon(al, log->logfile);
                break;

            case Log::Format::CLF_REFERER:
                Log::Format::SquidReferer(al, log->logfile);
                break;

            case Log::Format::CLF_USERAGENT:
                Log::Format::SquidUserAgent(al, log->logfile);
                break;

            case Log::Format::CLF_CUSTOM:
                Log::Format::SquidCustom(al, log);
                break;

#if ICAP_CLIENT
            case Log::Format::CLF_ICAP_SQUID:
                Log::Format::SquidIcap(al, log->logfile);
                break;
#endif

            default:
                fatalf("Unknown log format %d\n", log->type);
                break;
            }

            logfileLineEnd(log->logfile);
        }

        // NP:  WTF?  if _any_ log line has no checklist ignore the following ones?
        if (!checklist)
            break;
    }
}