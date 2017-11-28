        storeAppendPrintf(entry, "%s %s\n", name, var);
}

static void
parse_string(char **var)
{
    char *token = ConfigParser::NextToken();
    safe_free(*var);

    if (token == NULL)
        self_destruct();

    *var = xstrdup(token);
}

static void
free_string(char **var)
