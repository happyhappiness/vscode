server_rec *h2_ctx_server_get(h2_ctx *ctx)
{
    return ctx? ctx->server : NULL;
}