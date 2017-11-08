static int intstrcmp(const char *s1, const char *s2)
{
    apr_int64_t i1 = apr_atoi64(s1);
    apr_int64_t i2 = apr_atoi64(s2);

    if (i1 < i2)
        return -1;
    else if (i1 == i2)
        return 0;
    else
        return 1;
}