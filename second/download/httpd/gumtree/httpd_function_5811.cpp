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