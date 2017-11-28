double
xatof(const char *token)
{
    char *end;
    double ret = strtod(token, &end);

    if (ret == 0 && end == token)
        self_destruct();

    return ret;
}