static helpEntry *helpEntries;
static int helpEntriesLen;

static sds cliVersion(void) {
    sds version;
    version = sdscatprintf(sdsempty(), "%s", REDIS_VERSION);

