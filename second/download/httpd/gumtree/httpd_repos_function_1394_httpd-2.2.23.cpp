static apr_status_t bail_out_on_error(http_ctx_t *ctx,
                                      ap_filter_t *f,
                                      int http_error)
{
    apr_bucket *e;
    apr_bucket_brigade *bb = ctx->bb;

    apr_brigade_cleanup(bb);
    e = ap_bucket_error_create(http_error,
                               NULL, f->r->pool,
                               f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    e = apr_bucket_eos_create(f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    ctx->eos_sent = 1;
    return ap_pass_brigade(f->r->output_filters, bb);
}