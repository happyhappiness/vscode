static const char *log_virtual_host(request_rec *r, char *a)
{
    return r->server->server_hostname;
}