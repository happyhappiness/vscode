static const char *log_request_method(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, r->method);
}