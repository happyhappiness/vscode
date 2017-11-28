long
xatol(const char *token)
{
    char *end;
    long ret = strtol(token, &end, 10);

    if (end == token || *end)
        self_destruct();

    return ret;
}