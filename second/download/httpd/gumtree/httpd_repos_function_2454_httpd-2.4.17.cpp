int h2_ctx_is_task(h2_ctx *ctx)
{
    return ctx && !!ctx->task_env;
}