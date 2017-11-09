static APR_INLINE int response_is_html(request_rec *r)
{
    char *ctype = ap_field_noparam(r->pool, r->content_type);

    return !ap_cstr_casecmp(ctype, "text/html")
        || !ap_cstr_casecmp(ctype, "application/xhtml+xml");
}