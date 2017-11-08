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
            /* XXX should this use a separate deferred write pool, like
             * the original ap_core_output_filter?
             */
            ap_save_brigade(f, &(ctx->buffered_bb), &bb, c->pool);
            apr_brigade_cleanup(bb);
        }
    }
}