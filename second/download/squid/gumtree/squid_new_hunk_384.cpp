
        storeAppendPrintf(entry, "\n");
    }
}

static void
free_access_log(CustomLog ** definitions)
{
    while (*definitions) {
        CustomLog *log = *definitions;
        *definitions = log->next;

        log->logFormat = NULL;
        log->type = Log::Format::CLF_UNKNOWN;

        if (log->aclList)
