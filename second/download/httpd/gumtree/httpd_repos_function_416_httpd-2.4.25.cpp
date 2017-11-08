static const char *log_header_out(request_rec *r, char *a)
{
    const char *cp = NULL;

    if (!strcasecmp(a, "Content-type") && r->content_type) {
        cp = ap_field_noparam(r->pool, r->content_type);
    }
    else if (!strcasecmp(a, "Set-Cookie")) {
        cp = find_multiple_headers(r->pool, r->headers_out, a);
    }
    else {
        cp = apr_table_get(r->headers_out, a);
    }

    return ap_escape_logitem(r->pool, cp);
}