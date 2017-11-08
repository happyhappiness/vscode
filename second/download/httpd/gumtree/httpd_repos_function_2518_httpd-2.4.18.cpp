h2_ctx *h2_ctx_create_for(const conn_rec *c, h2_task *task)
{
    h2_ctx *ctx = h2_ctx_create(c);
    if (ctx) {
        ctx->task = task;
    }
    return ctx;
}