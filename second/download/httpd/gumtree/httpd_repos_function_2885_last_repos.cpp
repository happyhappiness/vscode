static apr_status_t push_request_somewhere(h2_proxy_ctx *ctx, request_rec *r)
{
    conn_rec *c = ctx->owner;
    const char *engine_type, *hostname;
    
    hostname = (ctx->p_conn->ssl_hostname? 
                ctx->p_conn->ssl_hostname : ctx->p_conn->hostname);
    engine_type = apr_psprintf(ctx->pool, "proxy_http2 %s%s", hostname, 
                               ctx->server_portstr);
    
    if (c->master && req_engine_push && r && is_h2 && is_h2(c)) {
        /* If we are have req_engine capabilities, push the handling of this
         * request (e.g. slave connection) to a proxy_http2 engine which 
         * uses the same backend. We may be called to create an engine 
         * ourself. */
        if (req_engine_push(engine_type, r, proxy_engine_init) == APR_SUCCESS) {
            if (ctx->engine == NULL) {
                /* request has been assigned to an engine in another thread */
                return SUSPENDED;
            }
        }
    }
    
    if (!ctx->engine) {
        /* No engine was available or has been initialized, handle this
         * request just by ourself. */
        ctx->engine_id = apr_psprintf(ctx->pool, "eng-proxy-%ld", c->id);
        ctx->engine_type = engine_type;
        ctx->engine_pool = ctx->pool;
        ctx->req_buffer_size = (32*1024);
        ctx->standalone = 1;
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                      "h2_proxy_http2(%ld): setup standalone engine for type %s", 
                      c->id, engine_type);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                      "H2: hosting engine %s", ctx->engine_id);
    }

    return h2_proxy_fifo_push(ctx->requests, r);
}