h2_ctx *h2_ctx_protocol_set(h2_ctx *ctx, const char *proto)
{
    ctx->protocol = proto;
    return ctx;
}