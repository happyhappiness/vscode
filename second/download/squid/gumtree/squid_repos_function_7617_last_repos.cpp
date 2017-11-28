void
base64_decode_init(struct base64_decode_ctx *ctx)
{
    ctx->word = ctx->bits = ctx->padding = 0;
}