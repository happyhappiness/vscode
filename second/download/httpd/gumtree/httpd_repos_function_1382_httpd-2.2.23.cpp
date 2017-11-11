static apr_port_t http_port(const request_rec *r)
{
    if (r->server->server_scheme &&
        (strcmp(r->server->server_scheme, "https") == 0))
        return DEFAULT_HTTPS_PORT;
    
    return DEFAULT_HTTP_PORT;
}