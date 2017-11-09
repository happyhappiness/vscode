h2_ctx *h2_ctx_get(const conn_rec *c, int create)
{
    h2_ctx *ctx = (h2_ctx*)ap_get_module_config(c->conn_config, &http2_module);
    if (ctx == NULL && create) {
        ctx = h2_ctx_create(c);
    }
    return ctx;
}