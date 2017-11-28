static void
parse_string(char **var)
{
    char *token = strtok(NULL, w_space);
    safe_free(*var);

    if (token == NULL)
        self_destruct();

    *var = xstrdup(token);
}