static int cpystrn(char *buf, const char *arg, int buflen)
{
    char *end;
    if (!arg)
        return 0;
    end = apr_cpystrn(buf, arg, buflen);
    return end - buf;
}