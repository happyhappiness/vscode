static char *rewrite_mapfunc_toupper(request_rec *r, char *key)
{
    char *p;

    for (p = key; *p; ++p) {
        *p = apr_toupper(*p);
    }

    return key;
}