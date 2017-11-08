static const char *log_request_file(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, r->filename);
}