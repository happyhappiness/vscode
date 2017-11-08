static void *hc_create_config(apr_pool_t *p, server_rec *s)
{
    sctx_t *ctx = (sctx_t *) apr_palloc(p, sizeof(sctx_t));
    apr_pool_create(&ctx->p, p);
    ctx->ba = apr_bucket_alloc_create(p);
    ctx->templates = apr_array_make(p, 10, sizeof(hc_template_t));
    ctx->conditions = apr_table_make(p, 10);
    ctx->hcworkers = apr_hash_make(p);
    ctx->tpsize = HC_THREADPOOL_SIZE;
    ctx->s = s;

    return ctx;
}