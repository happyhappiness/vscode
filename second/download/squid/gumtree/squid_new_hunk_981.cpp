free_int(int *var)
{
    *var = 0;
}

static void
dump_int64_t(StoreEntry * entry, const char *name, int64_t var)
{
    storeAppendPrintf(entry, "%s %" PRId64 "\n", name, var);
}

void
parse_int64_t(int64_t *var)
{
    int64_t i;
    i = GetInteger64();
    *var = i;
}

static void
free_int64_t(int64_t *var)
{
    *var = 0;
}

static void
dump_onoff(StoreEntry * entry, const char *name, int var)
{
    storeAppendPrintf(entry, "%s %s\n", name, var ? "on" : "off");
}

void
parse_onoff(int *var)
{
    char *token = ConfigParser::NextToken();
    if (!token) {
        self_destruct();
        return;
    }

    if (!strcmp(token, "on")) {
        *var = 1;
    } else if (!strcmp(token, "enable")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'enable' is deprecated. Please update to use 'on'.");
        *var = 1;
