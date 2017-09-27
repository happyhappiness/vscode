                                        request_rec *r,
                                        http2_output_consumed **pconsumed,
                                        void **pctx)
{
    h2_proxy_ctx *ctx = ap_get_module_config(r->connection->conn_config, 
                                             &proxy_http2_module);
    if (!ctx) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(03368)
                      "h2_proxy_session, engine init, no ctx found");
        return APR_ENOTIMPL;
    }
    
    ctx->pool = pool;
    ctx->engine = engine;
    ctx->engine_id = id;
    ctx->engine_type = type;
    ctx->engine_pool = pool;
    ctx->req_buffer_size = req_buffer_size;
    ctx->capacity = H2MIN(100, h2_proxy_fifo_capacity(ctx->requests));
    
    *pconsumed = out_consumed;
    *pctx = ctx;
    return APR_SUCCESS;
}

static apr_status_t add_request(h2_proxy_session *session, request_rec *r)
{
    h2_proxy_ctx *ctx = session->user_data;
    const char *url;
