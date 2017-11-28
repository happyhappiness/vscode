
        storeAppendPrintf(entry, "\n");
    }
}

static void
free_access_log(customlog ** definitions)
{
    while (*definitions) {
        customlog *log = *definitions;
        *definitions = log->next;

        log->logFormat = NULL;
        log->type = Log::Format::CLF_UNKNOWN;

        if (log->aclList)
