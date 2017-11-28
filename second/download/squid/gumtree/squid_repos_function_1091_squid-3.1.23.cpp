static void
parse_tristate(int *var)
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