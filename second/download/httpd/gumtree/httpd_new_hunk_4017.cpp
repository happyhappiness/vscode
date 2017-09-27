    x.pool = pool;
    apr_table_do(set_h1_header, &x, header, NULL);
    return APR_SUCCESS;
}


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

apr_status_t h2_request_rwrite(h2_request *req, request_rec *r)
{
    apr_status_t status;
    const char *scheme, *authority;
    
    scheme = (r->parsed_uri.scheme? r->parsed_uri.scheme
              : ap_http_scheme(r));
    authority = r->hostname;
    if (!ap_strchr_c(authority, ':') && r->server && r->server->port) {
        apr_port_t defport = apr_uri_port_of_scheme(scheme);
        if (defport != r->server->port) {
            /* port info missing and port is not default for scheme: append */
            authority = apr_psprintf(r->pool, "%s:%d", authority,
                                     (int)r->server->port);
        }
    }
    
    status = h2_request_make(req, r->pool,  r->method, scheme, authority,
                             apr_uri_unparse(r->pool, &r->parsed_uri, 
                                             APR_URI_UNP_OMITSITEPART),
                             r->headers_in);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): rwrite %s host=%s://%s%s",
                  req->id, req->method, req->scheme, req->authority, req->path);
    return status;
}

apr_status_t h2_request_add_header(h2_request *req, apr_pool_t *pool, 
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
