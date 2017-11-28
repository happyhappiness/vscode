void
base64_encode_init(struct base64_encode_ctx *ctx)
{
    ctx->word = ctx->bits = 0;
}