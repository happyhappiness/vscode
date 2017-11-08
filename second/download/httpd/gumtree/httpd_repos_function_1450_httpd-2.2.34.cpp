static int is_quoted_pair(const char *s)
{
    int res = -1;
    int c;

    if (*s == '\\') {
        c = (int) *(s + 1);
        if (c && apr_isascii(c)) {
            res = 1;
        }
    }
    return (res);
}