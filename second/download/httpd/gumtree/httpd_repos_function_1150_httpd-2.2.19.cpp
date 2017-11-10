static char *rewrite_mapfunc_escape(request_rec *r, char *key)
{
    return ap_escape_uri(r->pool, key);
}