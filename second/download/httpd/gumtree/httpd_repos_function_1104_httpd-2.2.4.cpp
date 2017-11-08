static char *rewrite_mapfunc_tolower(request_rec *r, char *key)
{
    char *p;

    for (p = key; *p; ++p) {
        *p = apr_tolower(*p);
    }

    return key;
}