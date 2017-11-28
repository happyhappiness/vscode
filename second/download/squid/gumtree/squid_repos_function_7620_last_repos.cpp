int
base64_decode_final(struct base64_decode_ctx *ctx)
{
    return ctx->bits == 0;
}