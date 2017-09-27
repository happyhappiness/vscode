    x.pool = pool;
    apr_table_do(set_h1_header, &x, header, NULL);
    return APR_SUCCESS;
}


apr_status_t h2_request_rwrite(h2_request *req, request_rec *r)
{
    apr_status_t status;
    
    req->config    = h2_config_rget(r);
    req->method    = r->method;
    req->scheme    = (r->parsed_uri.scheme? r->parsed_uri.scheme
                      : ap_http_scheme(r));
    req->authority = r->hostname;
    req->path      = apr_uri_unparse(r->pool, &r->parsed_uri, 
                                     APR_URI_UNP_OMITSITEPART);

    if (!ap_strchr_c(req->authority, ':') && r->server && r->server->port) {
        apr_port_t defport = apr_uri_port_of_scheme(req->scheme);
        if (defport != r->server->port) {
            /* port info missing and port is not default for scheme: append */
            req->authority = apr_psprintf(r->pool, "%s:%d", req->authority,
                                          (int)r->server->port);
        }
    }
    
    AP_DEBUG_ASSERT(req->scheme);
    AP_DEBUG_ASSERT(req->authority);
    AP_DEBUG_ASSERT(req->path);
    AP_DEBUG_ASSERT(req->method);

    status = add_all_h1_header(req, r->pool, r->headers_in);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                  "h2_request(%d): rwrite %s host=%s://%s%s",
                  req->id, req->method, req->scheme, req->authority, req->path);
                  
    return status;
}

apr_status_t h2_request_add_header(h2_request *req, apr_pool_t *pool, 
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
