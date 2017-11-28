int
etagParseInit(ETag * etag, const char *str)
{
    int len;
    assert(etag && str);
    etag->str = NULL;
    etag->weak = !strncmp(str, "W/", 2);

    if (etag->weak)
        str += 2;

    /* check format (quoted-string) */
    len = strlen(str);

    if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
        etag->str = str;

    return etag->str != NULL;
}