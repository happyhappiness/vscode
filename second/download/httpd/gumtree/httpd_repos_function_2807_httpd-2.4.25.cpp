static h2_ctx *h2_ctx_create(const conn_rec *c)
{
    h2_ctx *ctx = apr_pcalloc(c->pool, sizeof(h2_ctx));
    ap_assert(ctx);
    ap_set_module_config(c->conn_config, &http2_module, ctx);
    h2_ctx_server_set(ctx, c->base_server);
    return ctx;
}