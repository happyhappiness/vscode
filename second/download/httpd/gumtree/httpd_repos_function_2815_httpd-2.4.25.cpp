void h2_ctx_session_set(h2_ctx *ctx, struct h2_session *session)
{
    ctx->session = session;
}