h2_request *h2_req_create(int id, apr_pool_t *pool, const char *method, 
                          const char *scheme, const char *authority, 
                          const char *path, apr_table_t *header, int serialize)
{
    h2_request *req = apr_pcalloc(pool, sizeof(h2_request));
    
    req->method         = method;
    req->scheme         = scheme;
    req->authority      = authority;
    req->path           = path;
    req->headers        = header? header : apr_table_make(pool, 10);
    req->request_time   = apr_time_now();
    req->serialize      = serialize;
    
    return req;
}