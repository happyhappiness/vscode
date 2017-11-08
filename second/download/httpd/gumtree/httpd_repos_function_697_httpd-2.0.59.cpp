void ssl_util_strupper(char *s)
{
    for (; *s; ++s)
        *s = apr_toupper(*s);
    return;
}