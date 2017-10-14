apr_status_t h2_request_rwrite(h2_request *req, request_rec *r, h2_mplx *m)
{
    apr_status_t status;
    req->method = r->method;
    req->authority = r->hostname;
    req->path = r->uri;
    if (!ap_strchr_c(req->authority, ':') && r->parsed_uri.port_str) {
        req->authority = apr_psprintf(req->pool, "%s:%s", req->authority,
                                      r->parsed_uri.port_str);
    }
    req->scheme = NULL;
    
    
    status = insert_request_line(req, m);
    if (status == APR_SUCCESS) {
        status = h2_to_h1_add_headers(req->to_h1, r->headers_in);
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                  "h2_request(%d): written request %s %s, host=%s",
                  req->id, req->method, req->path, req->authority);
    
    return status;
}