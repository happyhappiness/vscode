    storeAppendPrintf(entry, "%s %s\n", name, var ? "on" : "off");
}

void
parse_onoff(int *var)
{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    if (!strcmp(token, "on")) {
        *var = 1;
