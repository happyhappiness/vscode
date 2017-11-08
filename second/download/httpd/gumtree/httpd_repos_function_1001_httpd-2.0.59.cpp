static char *rewrite_mapfunc_unescape(request_rec *r, char *key)
{
    char *value;

    value = apr_pstrdup(r->pool, key);
    ap_unescape_url(value);
    return value;
}