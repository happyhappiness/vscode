        logs = &(*logs)->next;

    *logs = cl;
}

static int
check_null_access_log(CustomLog *customlog_definitions)
{
    return customlog_definitions == NULL;
}

static void
dump_access_log(StoreEntry * entry, const char *name, CustomLog * logs)
{
    CustomLog *log;

    for (log = logs; log; log = log->next) {
        storeAppendPrintf(entry, "%s ", name);

        switch (log->type) {

