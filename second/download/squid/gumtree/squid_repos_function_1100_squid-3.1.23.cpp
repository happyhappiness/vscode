void
parse_eol(char *volatile *var)
{
    if (!var) {
        self_destruct();
        return;
    }

    unsigned char *token = (unsigned char *) strtok(NULL, null_string);
    safe_free(*var);

    if (!token) {
        self_destruct();
        return;
    }

    while (*token && xisspace(*token))
        token++;

    if (!*token) {
        self_destruct();
        return;
    }

    *var = xstrdup((char *) token);
}