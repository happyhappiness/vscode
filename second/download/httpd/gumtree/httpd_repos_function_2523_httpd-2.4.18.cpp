h2_ctx *h2_ctx_server_set(h2_ctx *ctx, server_rec *s)
{
    ctx->server = s;
    return ctx;
}