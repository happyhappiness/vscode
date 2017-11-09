static void pappend(saxctxt *ctx, const char *buf, const size_t len)
{
    preserve(ctx, len);
    memcpy(ctx->buf+ctx->offset, buf, len);
    ctx->offset += len;
}