static const char *log_request_protocol(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, r->protocol);
}