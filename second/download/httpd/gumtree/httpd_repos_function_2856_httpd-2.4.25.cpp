const h2_config *h2_config_get(conn_rec *c)
{
    h2_ctx *ctx = h2_ctx_get(c, 0);
    
    if (ctx) {
        if (ctx->config) {
            return ctx->config;
        }
        else if (ctx->server) {
            ctx->config = h2_config_sget(ctx->server);
            return ctx->config;
        }
    }
    
    return h2_config_sget(c->base_server);
}