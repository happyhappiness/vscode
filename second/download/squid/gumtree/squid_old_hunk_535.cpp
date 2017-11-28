{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    if (!strcasecmp(token, "on")) {
        *var = 1;
    } else if (!strcasecmp(token, "enable")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'enable' is deprecated. Please update to use value 'on'.");
        *var = 1;
    } else if (!strcasecmp(token, "warn")) {
        *var = -1;
    } else if (!strcasecmp(token, "off")) {
        *var = 0;
    } else if (!strcasecmp(token, "disable")) {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'disable' is deprecated. Please update to use value 'off'.");
        *var = 0;
    } else {
        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Invalid option: Tristate options can only be 'on', 'off', or 'warn'.");
        self_destruct();
    }
}

#define free_tristate free_int

static void
dump_refreshpattern(StoreEntry * entry, const char *name, RefreshPattern * head)
{
    while (head != NULL) {
        storeAppendPrintf(entry, "%s%s %s %d %d%% %d",
                          name,
