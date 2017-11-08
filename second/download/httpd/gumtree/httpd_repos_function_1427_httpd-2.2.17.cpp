static int is_qtext(char c)
{
    int res;

    res = (apr_isascii(c) && (c != '"') && (c != '\\') && (c != '\n'))
        ? 1 : -1;
    return res;
}