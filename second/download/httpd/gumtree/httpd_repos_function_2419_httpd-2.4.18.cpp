h2_request *h2_request_createn(int id, apr_pool_t *pool,
                               const struct h2_config *config, 
                               const char *method, const char *scheme,
                               const char *authority, const char *path,
                               apr_table_t *header)
{
    h2_request *req = apr_pcalloc(pool, sizeof(h2_request));
    
    req->id             = id;
    req->config         = config;
    req->method         = method;
    req->scheme         = scheme;
    req->authority      = authority;
    req->path           = path;
    req->headers        = header? header : apr_table_make(pool, 10);
    req->request_time   = apr_time_now();

    return req;
}