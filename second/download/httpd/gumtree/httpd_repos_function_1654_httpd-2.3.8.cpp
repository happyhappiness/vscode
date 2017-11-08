static void timed_cleanup_callback(void *baton)
{
    s_baton_t *ctx = baton;
    
    /* Causes all serf connections to unregister from the event mpm */
    if (ctx->rstatus) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, ctx->rstatus, ctx->r,
                      "serf: request returned: %d", ctx->rstatus);
        ctx->r->status = HTTP_OK;
        apr_pool_destroy(ctx->serf_pool);
        ap_die(ctx->rstatus, ctx->r);
    }
    else {
        apr_bucket *e;
        apr_brigade_cleanup(ctx->tmpbb);
        e = apr_bucket_flush_create(ctx->r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->tmpbb, e);
        e = apr_bucket_eos_create(ctx->r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(ctx->tmpbb, e);

        /* TODO: return code? bleh */
        ap_pass_brigade(ctx->r->output_filters, ctx->tmpbb);
        
        apr_pool_destroy(ctx->serf_pool);

        ap_finalize_request_protocol(ctx->r);
        ap_process_request_after_handler(ctx->r);
        return;
    }
}