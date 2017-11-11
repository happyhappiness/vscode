static int is_token(char c)
{
    int res;

    res = (apr_isascii(c) && apr_isgraph(c)
           && (strchr(tspecial, c) == NULL)) ? 1 : -1;
    return res;
}