h2_task *h2_ctx_get_task(h2_ctx *ctx)
{
    return ctx? ctx->task : NULL;
}