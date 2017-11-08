static const char *log_header_in(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, apr_table_get(r->headers_in, a));
}