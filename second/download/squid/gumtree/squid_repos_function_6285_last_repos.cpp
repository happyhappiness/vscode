static char *
squidaio_xstrdup(const char *str)
{
    char *p;
    int len = strlen(str) + 1;

    p = (char *)squidaio_xmalloc(len);
    strncpy(p, str, len);

    return p;
}