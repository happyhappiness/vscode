static const char *log_header_out(request_rec *r, char *a)
{
    const char *cp = apr_table_get(r->headers_out, a);
    if (!strcasecmp(a, "Content-type") && r->content_type) {
        cp = ap_field_noparam(r->pool, r->content_type);
    }
    if (cp) {
        return cp;
    }
    return apr_table_get(r->err_headers_out, a);
}