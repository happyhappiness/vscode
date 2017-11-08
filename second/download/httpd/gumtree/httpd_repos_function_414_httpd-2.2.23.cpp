static const char *log_virtual_host(request_rec *r, char *a)
{
    return ap_escape_logitem(r->pool, r->server->server_hostname);
}