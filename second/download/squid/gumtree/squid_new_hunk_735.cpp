}

#define dump_eol dump_string
#define free_eol free_string

static void
parse_TokenOrQuotedString(char **var)
{
    char *token = ConfigParser::NextQuotedToken();
    safe_free(*var);

    if (token == NULL)
        self_destruct();

    *var = xstrdup(token);
}

#define dump_TokenOrQuotedString dump_string
#define free_TokenOrQuotedString free_string

static void
dump_time_t(StoreEntry * entry, const char *name, time_t var)
{
    storeAppendPrintf(entry, "%s %d seconds\n", name, (int) var);
}

void
