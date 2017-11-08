static APR_INLINE int response_is_html(request_rec *r)
{
    char *ctype = ap_field_noparam(r->pool, r->content_type);
    ap_str_tolower(ctype);
    return !strcmp(ctype, "text/html")
        || !strcmp(ctype, "application/xhtml+xml");
}