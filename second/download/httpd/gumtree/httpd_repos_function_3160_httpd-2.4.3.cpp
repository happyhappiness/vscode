static void setaside_remaining_output(ap_filter_t *f,
                                      core_output_filter_ctx_t *ctx,
                                      apr_bucket_brigade *bb,
                                      conn_rec *c)
{
    if (bb == NULL) {
        return;
    }
    remove_empty_buckets(bb);
    if (!APR_BRIGADE_EMPTY(bb)) {
        c->data_in_output_filters = 1;
        if (bb != ctx->buffered_bb) {
            if (!ctx->deferred_write_pool) {
                apr_pool_create(&ctx->deferred_write_pool, c->pool);
                apr_pool_tag(ctx->deferred_write_pool, "deferred_write");
            }
            ap_save_brigade(f, &(ctx->buffered_bb), &bb,
                            ctx->deferred_write_pool);
            apr_brigade_cleanup(bb);
        }
    }
    else if (ctx->deferred_write_pool) {
        /*
         * There are no more requests in the pipeline. We can just clear the
         * pool.
         */
        apr_pool_clear(ctx->deferred_write_pool);
    }
}