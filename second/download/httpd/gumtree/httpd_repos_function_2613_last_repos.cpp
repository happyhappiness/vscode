static int icollect_iter(void *x, void *val)
{
    icollect_ctx *ctx = x;
    if (ctx->len < ctx->max) {
        ctx->buffer[ctx->len++] = *((int*)((char *)val + ctx->ih->ioff));
        return 1;
    }
    return 0;
}