static apr_status_t init_context(ap_filter_t *f, sed_expr_config *sed_cfg, int usetpool)
{
    apr_status_t status;
    sed_filter_ctxt* ctx;
    request_rec *r = f->r;
    /* Create the context. Call sed_init_eval. libsed will generated
     * output by calling sed_write_output and generates any error by
     * invoking log_sed_errf.
     */
    ctx = apr_pcalloc(r->pool, sizeof(sed_filter_ctxt));
    ctx->r = r;
    ctx->bb = NULL;
    ctx->numbuckets = 0;
    ctx->f = f;
    status = sed_init_eval(&ctx->eval, sed_cfg->sed_cmds, log_sed_errf,
                           r, &sed_write_output, r->pool);
    if (status != APR_SUCCESS) {
        return status;
    }
    apr_pool_cleanup_register(r->pool, &ctx->eval, sed_eval_cleanup,
                              apr_pool_cleanup_null);
    ctx->bufsize = MODSED_OUTBUF_SIZE;
    if (usetpool) {
        apr_pool_create(&(ctx->tpool), r->pool);
    }
    else {
        ctx->tpool = r->pool;
    }
    alloc_outbuf(ctx);
    f->ctx = ctx;
    return APR_SUCCESS;
}