static const char *log_trailer_out(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, apr_table_get(r->trailers_out, a));
}