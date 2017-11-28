check_null_access_log(customlog *customlog_definitions)
{
    return customlog_definitions == NULL;
}

static void
dump_logformat(StoreEntry * entry, const char *name, logformat * definitions)
{
    accessLogDumpLogFormat(entry, name, definitions);
}

static void
dump_access_log(StoreEntry * entry, const char *name, customlog * logs)
{
    customlog *log;

    for (log = logs; log; log = log->next) {
        storeAppendPrintf(entry, "%s ", name);

        switch (log->type) {

        case CLF_CUSTOM:
            storeAppendPrintf(entry, "%s %s", log->filename, log->logFormat->name);
            break;

        case CLF_NONE:
            storeAppendPrintf(entry, "none");
            break;

        case CLF_SQUID:
            storeAppendPrintf(entry, "%s squid", log->filename);
            break;

        case CLF_COMMON:
            storeAppendPrintf(entry, "%s squid", log->filename);
            break;
#if ICAP_CLIENT
        case CLF_ICAP_SQUID:
            storeAppendPrintf(entry, "%s icap_squid", log->filename);
            break;
#endif
        case CLF_AUTO:

            if (log->aclList)
                storeAppendPrintf(entry, "%s auto", log->filename);
            else
                storeAppendPrintf(entry, "%s", log->filename);

            break;

        case CLF_UNKNOWN:
            break;
        }

        if (log->aclList)
            dump_acl_list(entry, log->aclList);

        storeAppendPrintf(entry, "\n");
    }
}

static void
free_logformat(logformat ** definitions)
{
    while (*definitions) {
        logformat *format = *definitions;
        *definitions = format->next;
        safe_free(format->name);
        accessLogFreeLogFormat(&format->format);
        xfree(format);
    }
}

static void
free_access_log(customlog ** definitions)
{
    while (*definitions) {
        customlog *log = *definitions;
        *definitions = log->next;

        log->logFormat = NULL;
        log->type = CLF_UNKNOWN;

        if (log->aclList)
            aclDestroyAclList(&log->aclList);

        safe_free(log->filename);

        xfree(log);
    }
}

#if USE_ADAPTATION

static void
parse_adaptation_service_set_type()
{
    Adaptation::Config::ParseServiceSet();
