h2_session *h2_ctx_session_get(h2_ctx *ctx)
{
    return ctx? ctx->session : NULL;
}