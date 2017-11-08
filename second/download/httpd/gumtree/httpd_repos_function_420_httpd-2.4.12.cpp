static const char *log_trailer_in(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, apr_table_get(r->trailers_in, a));
}