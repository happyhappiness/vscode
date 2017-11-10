static void *hm_create_config(apr_pool_t *p, server_rec *s)
{
    hm_ctx_t *ctx = (hm_ctx_t *) apr_palloc(p, sizeof(hm_ctx_t));

    ctx->active = 0;
    ctx->storage_path = ap_server_root_relative(p, "logs/hb.dat");
    /* TODO: Add directive for tuning the update interval
     */
    ctx->interval = apr_time_from_sec(HM_UPDATE_SEC);
    ctx->s = s;
    apr_pool_create(&ctx->p, p);
    ctx->servers = apr_hash_make(ctx->p);

    return ctx;
}