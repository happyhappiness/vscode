static char *rewrite_mapfunc_unescape(request_rec *r, char *key)
{
    ap_unescape_url(key);

    return key;
}