static const char *http_scheme(const request_rec *r)
{
    /* 
     * The http module shouldn't return anything other than 
     * "http" (the default) or "https".
     */
    if (r->server->server_scheme &&
        (strcmp(r->server->server_scheme, "https") == 0))
        return "https";
    
    return "http";
}