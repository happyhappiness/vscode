        if (!h2_allows_h2_upgrade(c)) {
            return DECLINED;
        }
         
        p = apr_table_get(r->headers_in, "HTTP2-Settings");
        if (!p) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "upgrade without HTTP2-Settings declined");
            return DECLINED;
        }
        
        p = apr_table_get(r->headers_in, "Connection");
        if (!ap_find_token(r->pool, p, "http2-settings")) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "upgrade without HTTP2-Settings declined");
            return DECLINED;
        }
        
        /* We also allow switching only for requests that have no body.
         */
        p = apr_table_get(r->headers_in, "Content-Length");
        if (p && strcmp(p, "0")) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "upgrade with content-length: %s, declined", p);
            return DECLINED;
        }
    }
    
    while (*protos) {
