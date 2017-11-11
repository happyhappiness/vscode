static char *rewrite_mapfunc_toupper(request_rec *r, char *key)
{
    ap_str_toupper(key);

    return key;
}