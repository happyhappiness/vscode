static void out_consumed(void *baton, conn_rec *c, apr_off_t bytes)
{
    h2_proxy_ctx *ctx = baton;
    
    if (ctx->session) {
        h2_proxy_session_update_window(ctx->session, c, bytes);
    }
}