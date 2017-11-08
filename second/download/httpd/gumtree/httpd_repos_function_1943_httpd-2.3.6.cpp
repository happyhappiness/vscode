static apr_status_t append_bucket(sed_filter_ctxt* ctx, char* buf, int sz)
{
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b;
    if (ctx->tpool == ctx->r->pool) {
        /* We are not using transient bucket */
        b = apr_bucket_pool_create(buf, sz, ctx->r->pool,
                                   ctx->r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
    }
    else {
        /* We are using transient bucket */
        b = apr_bucket_transient_create(buf, sz,
                                        ctx->r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
        ctx->numbuckets++;
        if (ctx->numbuckets >= MAX_TRANSIENT_BUCKETS) {
            b = apr_bucket_flush_create(ctx->r->connection->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, b);
            status = ap_pass_brigade(ctx->f->next, ctx->bb);
            apr_brigade_cleanup(ctx->bb);
            clear_ctxpool(ctx);
        }
    }
    return status;
}