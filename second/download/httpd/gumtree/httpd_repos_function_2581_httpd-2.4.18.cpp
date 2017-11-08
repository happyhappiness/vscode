int h2_h2_process_conn(conn_rec* c)
{
    h2_ctx *ctx = h2_ctx_get(c);
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, process_conn");
    if (h2_ctx_is_task(ctx)) {
        /* our stream pseudo connection */
        return DECLINED;
    }

    if (h2_ctx_protocol_get(c)) {
        /* Something has been negotiated */
    }
    else if (!strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))
             && h2_allows_h2_direct(c) 
             && h2_is_acceptable_connection(c, 1)) {
        /* connection still is on http/1.1 and H2Direct is enabled. 
         * Otherwise connection is in a fully acceptable state.
         * -> peek at the first 24 incoming bytes
         */
        apr_bucket_brigade *temp;
        apr_status_t status;
        char *s = NULL;
        apr_size_t slen;
        
        temp = apr_brigade_create(c->pool, c->bucket_alloc);
        status = ap_get_brigade(c->input_filters, temp,
                                AP_MODE_SPECULATIVE, APR_BLOCK_READ, 24);
        
        if (status != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c,
                          "h2_h2, error reading 24 bytes speculative");
            apr_brigade_destroy(temp);
            return DECLINED;
        }
        
        apr_brigade_pflatten(temp, &s, &slen, c->pool);
        if ((slen >= 24) && !memcmp(H2_MAGIC_TOKEN, s, 24)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          "h2_h2, direct mode detected");
            h2_ctx_protocol_set(ctx, h2_h2_is_tls(c)? "h2" : "h2c");
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                          "h2_h2, not detected in %d bytes: %s", 
                          (int)slen, s);
        }
        
        apr_brigade_destroy(temp);
    }
    else {
        /* the connection is not HTTP/1.1 or not for us, don't touch it */
        return DECLINED;
    }

    /* If "h2" was selected as protocol (by whatever mechanism), take over
     * the connection.
     */
    if (h2_ctx_is_active(ctx)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_h2, connection, h2 active");
        
        return h2_conn_process(c, NULL, ctx->server);
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, declined");
    return DECLINED;
}