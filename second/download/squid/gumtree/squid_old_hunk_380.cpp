{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    if (!strcasecmp(token, "on") || !strcasecmp(token, "enable"))
        *var = 1;
    else if (!strcasecmp(token, "warn"))
        *var = -1;
    else
        *var = 0;
}

#define free_tristate free_int

static void
dump_refreshpattern(StoreEntry * entry, const char *name, refresh_t * head)
{
    while (head != NULL) {
        storeAppendPrintf(entry, "%s%s %s %d %d%% %d",
                          name,
                          head->flags.icase ? " -i" : null_string,
                          head->pattern,
