int h2_ctx_is_active(h2_ctx *ctx)
{
    return ctx && ctx->is_h2;
}