static const char *log_note(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, apr_table_get(r->notes, a));
}