const char *h2_ctx_protocol_get(const conn_rec *c)
{
    h2_ctx *ctx;
    if (c->master) {
        c = c->master;
    }
    ctx = (h2_ctx*)ap_get_module_config(c->conn_config, &http2_module);
    return ctx? ctx->protocol : NULL;
}