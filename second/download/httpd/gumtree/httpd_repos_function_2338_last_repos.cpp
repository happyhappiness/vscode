static const char *inv_field_name_chr(const char *token)
{
    const char *p = ap_scan_http_token(token);
    if (p == token && *p == ':') {
        p = ap_scan_http_token(++p);
    }
    return (p && *p)? p : NULL;
}