static char *rewrite_mapfunc_toupper(request_rec *r, char *key)
{
    char *value, *cp;

    for (cp = value = apr_pstrdup(r->pool, key); cp != NULL && *cp != '\0';
         cp++) {
        *cp = apr_toupper(*cp);
    }
    return value;
}