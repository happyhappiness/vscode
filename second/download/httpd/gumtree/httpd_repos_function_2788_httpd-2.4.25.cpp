static h2_proxy_ctx *push_request_somewhere(h2_proxy_ctx *ctx)
{
    conn_rec *c = ctx->owner;
    const char *engine_type, *hostname;
    
    hostname = (ctx->p_conn->ssl_hostname? 
                ctx->p_conn->ssl_hostname : ctx->p_conn->hostname);
    engine_type = apr_psprintf(ctx->pool, "proxy_http2 %s%s", hostname, 
                               ctx->server_portstr);
    
    if (c->master && req_engine_push && ctx->next && is_h2 && is_h2(c)) {
        /* If we are have req_engine capabilities, push the handling of this
         * request (e.g. slave connection) to a proxy_http2 engine which 
         * uses the same backend. We may be called to create an engine 
         * ourself. */
        if (req_engine_push(engine_type, ctx->next, proxy_engine_init)
            == APR_SUCCESS) {
            /* to renew the lifetime, we might have set a new ctx */
            ctx = ap_get_module_config(c->conn_config, &proxy_http2_module);
            if (ctx->engine == NULL) {
                /* Another engine instance has taken over processing of this
                 * request. */
                ctx->r_status = SUSPENDED;
                ctx->next = NULL;
                return ctx;
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
    return ctx;
}