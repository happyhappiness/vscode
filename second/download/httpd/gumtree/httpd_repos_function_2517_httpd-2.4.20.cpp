apr_status_t h2_request_make(h2_request *req, apr_pool_t *pool,
                             const char *method, const char *scheme, 
                             const char *authority, const char *path, 
                             apr_table_t *headers)
{
    req->method    = method;
    req->scheme    = scheme;
    req->authority = authority;
    req->path      = path;

    AP_DEBUG_ASSERT(req->scheme);
    AP_DEBUG_ASSERT(req->authority);
    AP_DEBUG_ASSERT(req->path);
    AP_DEBUG_ASSERT(req->method);

    return add_all_h1_header(req, pool, headers);
}