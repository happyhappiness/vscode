static const char *log_handler(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, r->handler);
}