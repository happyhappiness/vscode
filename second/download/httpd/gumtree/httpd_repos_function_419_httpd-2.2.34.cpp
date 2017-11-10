static const char *log_server_name(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, ap_get_server_name(r));
}