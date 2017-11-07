static int h2_protocol_propose(conn_rec *c, request_rec *r,
                               server_rec *s,
                               const apr_array_header_t *offers,
                               apr_array_header_t *proposals)
{
    int proposed = 0;
    int is_tls = h2_h2_is_tls(c);
    const char **protos = is_tls? h2_tls_protos : h2_clear_protos;
    
    (void)s;
    if (strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))) {
        /* We do not know how to switch from anything else but http/1.1.
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "protocol switch: current proto != http/1.1, declined");
        return DECLINED;
    }
    
    if (!h2_is_acceptable_connection(c, 0)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "protocol propose: connection requirements not met");
        return DECLINED;
    }
    
    if (r) {
        /* So far, this indicates an HTTP/1 Upgrade header initiated
         * protocol switch. For that, the HTTP2-Settings header needs
         * to be present and valid for the connection.
         */
        const char *p;
        
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
        /* Add all protocols we know (tls or clear) and that
         * are part of the offerings (if there have been any). 
         */
        if (!offers || ap_array_str_contains(offers, *protos)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          "proposing protocol '%s'", *protos);
            APR_ARRAY_PUSH(proposals, const char*) = *protos;
            proposed = 1;
        }
        ++protos;
    }
    return proposed? DECLINED : OK;
}