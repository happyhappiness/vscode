static void *lb_hb_create_config(apr_pool_t *p, server_rec *s)
{
    lb_hb_ctx_t *ctx = (lb_hb_ctx_t *) apr_palloc(p, sizeof(lb_hb_ctx_t));

    ctx->path = ap_runtime_dir_relative(p, DEFAULT_HEARTBEAT_STORAGE);

    return ctx;
}