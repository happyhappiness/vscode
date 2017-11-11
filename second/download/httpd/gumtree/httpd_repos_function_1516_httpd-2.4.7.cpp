static char *rewrite_mapfunc_tolower(request_rec *r, char *key)
{
    ap_str_tolower(key);

    return key;
}