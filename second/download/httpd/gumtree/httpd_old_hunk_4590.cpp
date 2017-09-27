                                        request_rec *r,
                                        http2_output_consumed **pconsumed,
                                        void **pctx)
{
    h2_proxy_ctx *ctx = ap_get_module_config(r->connection->conn_config, 
                                             &proxy_http2_module);
    if (ctx) {
        conn_rec *c = ctx->owner;
        h2_proxy_ctx *nctx;
        
        /* we need another lifetime for this. If we do not host
         * an engine, the context lives in r->pool. Since we expect
         * to server more than r, we need to live longer */
        nctx = apr_pcalloc(pool, sizeof(*nctx));
        if (nctx == NULL) {
            return APR_ENOMEM;
        }
        memcpy(nctx, ctx, sizeof(*nctx));
        ctx = nctx;
        ctx->pool = pool;
        ctx->engine = engine;
        ctx->engine_id = id;
        ctx->engine_type = type;
        ctx->engine_pool = pool;
        ctx->req_buffer_size = req_buffer_size;
        ctx->capacity = 100;

        ap_set_module_config(c->conn_config, &proxy_http2_module, ctx);

        *pconsumed = out_consumed;
        *pctx = ctx;
        return APR_SUCCESS;
    }
    ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(03368)
                  "h2_proxy_session, engine init, no ctx found");
    return APR_ENOTIMPL;
}

static apr_status_t add_request(h2_proxy_session *session, request_rec *r)
{
    h2_proxy_ctx *ctx = session->user_data;
    const char *url;
