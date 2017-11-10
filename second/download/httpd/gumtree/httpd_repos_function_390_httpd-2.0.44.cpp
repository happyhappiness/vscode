static const char *log_note(request_rec *r, char *a)
{
    return apr_table_get(r->notes, a);
}