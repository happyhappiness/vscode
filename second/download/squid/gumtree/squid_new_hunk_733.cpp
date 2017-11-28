    storeAppendPrintf(entry, "%s %s\n", name, state);
}

static void
parse_tristate(int *var)
{
    char *token = ConfigParser::NextToken();

    if (token == NULL)
        self_destruct();

    if (!strcmp(token, "on")) {
        *var = 1;
