static void clear_ctxpool(sed_filter_ctxt* ctx)
{
    apr_pool_clear(ctx->tpool);
    ctx->outbuf = NULL;
    ctx->curoutbuf = NULL;
    ctx->numbuckets = 0;
}