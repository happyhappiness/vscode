static char *rewrite_mapfunc_tolower(request_rec *r, char *key)
{
    char *value, *cp;

    for (cp = value = apr_pstrdup(r->pool, key); cp != NULL && *cp != '\0';
         cp++) {
        *cp = apr_tolower(*cp);
    }
    return value;
}