int h2_h2_process_conn(conn_rec* c)
{
    apr_status_t status;
    h2_ctx *ctx;
    
    if (c->master) {
        return DECLINED;
    }
    
    ctx = h2_ctx_get(c, 0);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, process_conn");
    if (h2_ctx_is_task(ctx)) {
        /* our stream pseudo connection */
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, "h2_h2, task, declined");
        return DECLINED;
    }
    
    if (!ctx && c->keepalives == 0) {
        const char *proto = ap_get_protocol(c);
        
        if (APLOGctrace1(c)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, process_conn, "
                          "new connection using protocol '%s', direct=%d, "
                          "tls acceptable=%d", proto, h2_allows_h2_direct(c), 
                          h2_is_acceptable_connection(c, 1));
        }
        
        if (!strcmp(AP_PROTOCOL_HTTP1, proto)
            && h2_allows_h2_direct(c) 
            && h2_is_acceptable_connection(c, 1)) {
            /* Fresh connection still is on http/1.1 and H2Direct is enabled. 
             * Otherwise connection is in a fully acceptable state.
             * -> peek at the first 24 incoming bytes
             */
            apr_bucket_brigade *temp;
            char *s = NULL;
            apr_size_t slen;
            
            temp = apr_brigade_create(c->pool, c->bucket_alloc);
            status = ap_get_brigade(c->input_filters, temp,
                                    AP_MODE_SPECULATIVE, APR_BLOCK_READ, 24);
            
            if (status != APR_SUCCESS) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03054)
                              "h2_h2, error reading 24 bytes speculative");
                apr_brigade_destroy(temp);
                return DECLINED;
            }
            
            apr_brigade_pflatten(temp, &s, &slen, c->pool);
            if ((slen >= 24) && !memcmp(H2_MAGIC_TOKEN, s, 24)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                              "h2_h2, direct mode detected");
                if (!ctx) {
                    ctx = h2_ctx_get(c, 1);
                }
                h2_ctx_protocol_set(ctx, h2_h2_is_tls(c)? "h2" : "h2c");
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                              "h2_h2, not detected in %d bytes: %s", 
                              (int)slen, s);
            }
            
            apr_brigade_destroy(temp);
        }
    }

    if (ctx) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "process_conn");
        if (!h2_ctx_session_get(ctx)) {
            status = h2_conn_setup(ctx, c, NULL);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c, "conn_setup");
            if (status != APR_SUCCESS) {
                return status;
            }
        }
        return h2_conn_run(ctx, c);
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, declined");
    return DECLINED;
}