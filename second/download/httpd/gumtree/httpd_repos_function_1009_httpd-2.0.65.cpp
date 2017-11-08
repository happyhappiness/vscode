static char *rewrite_mapfunc_escape(request_rec *r, char *key)
{
    char *value;

    value = ap_escape_uri(r->pool, key);
    return value;
}