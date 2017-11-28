void
parse_eol(char *volatile *var)
{
    unsigned char *token = (unsigned char *) strtok(NULL, null_string);
    safe_free(*var);

    if (token == NULL)
        self_destruct();

    while (*token && xisspace(*token))
        token++;

    if (!*token)
        self_destruct();

    *var = xstrdup((char *) token);
}