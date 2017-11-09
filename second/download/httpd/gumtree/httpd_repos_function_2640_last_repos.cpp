apr_status_t h2_proxy_req_make(h2_proxy_request *req, apr_pool_t *pool,
                         const char *method, const char *scheme, 
                         const char *authority, const char *path, 
                         apr_table_t *headers)
{
    h1_ctx x;

    req->method    = method;
    req->scheme    = scheme;
    req->authority = authority;
    req->path      = path;

    ap_assert(req->scheme);
    ap_assert(req->authority);
    ap_assert(req->path);
    ap_assert(req->method);

    x.pool = pool;
    x.headers = req->headers;
    apr_table_do(set_h1_header, &x, headers, NULL);
    return APR_SUCCESS;
}