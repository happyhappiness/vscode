static char *
read_get_request(void)
{
    char *s;

    if ((s = getenv("QUERY_STRING")) == NULL)
        return NULL;

    return xstrdup(s);
}