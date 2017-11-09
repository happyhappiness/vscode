static const char *inv_field_value_chr(const char *token)
{
    const char *p = ap_scan_http_field_content(token);
    return (p && *p)? p : NULL;
}