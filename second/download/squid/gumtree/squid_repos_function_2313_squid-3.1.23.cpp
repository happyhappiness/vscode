void
accessLogLogTo(customlog* log, AccessLogEntry * al, ACLChecklist * checklist)
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
        if (checklist && log->aclList && !checklist->matchAclListFast(log->aclList))
            continue;

        switch (log->type) {

        case CLF_AUTO:

            if (Config.onoff.common_log)
                accessLogCommon(al, log->logfile);
            else
                accessLogSquid(al, log->logfile);

            break;

        case CLF_SQUID:
            accessLogSquid(al, log->logfile);

            break;

        case CLF_COMMON:
            accessLogCommon(al, log->logfile);

            break;

        case CLF_CUSTOM:
            accessLogCustom(al, log);

            break;

#if ICAP_CLIENT
        case CLF_ICAP_SQUID:
            accessLogICAPSquid(al, log->logfile);

            break;
#endif

        case CLF_NONE:
            goto last;

        default:
            fatalf("Unknown log format %d\n", log->type);

            break;
        }

        logfileFlush(log->logfile);

        if (!checklist)
            break;
    }

last:
    (void)0; /* NULL statement for label */
}