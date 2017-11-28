    for (log = logs; log; log = log->next) {
        storeAppendPrintf(entry, "%s ", name);

        switch (log->type) {

        case Log::Format::CLF_CUSTOM:
            storeAppendPrintf(entry, "%s %s", log->filename, log->logFormat->name);
            break;

        case Log::Format::CLF_NONE:
            storeAppendPrintf(entry, "none");
            break;

        case Log::Format::CLF_SQUID:
            storeAppendPrintf(entry, "%s squid", log->filename);
            break;

        case Log::Format::CLF_COMBINED:
            storeAppendPrintf(entry, "%s combined", log->filename);
            break;

        case Log::Format::CLF_COMMON:
            storeAppendPrintf(entry, "%s common", log->filename);
            break;

#if ICAP_CLIENT
        case Log::Format::CLF_ICAP_SQUID:
            storeAppendPrintf(entry, "%s icap_squid", log->filename);
            break;
#endif
        case Log::Format::CLF_USERAGENT:
            storeAppendPrintf(entry, "%s useragent", log->filename);
            break;

        case Log::Format::CLF_REFERER:
            storeAppendPrintf(entry, "%s referrer", log->filename);
            break;

        case Log::Format::CLF_UNKNOWN:
            break;
        }

        if (log->aclList)
            dump_acl_list(entry, log->aclList);

        storeAppendPrintf(entry, "\n");
    }
}
