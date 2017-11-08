static apr_status_t send_bucket_downstream(ap_filter_t *f, apr_bucket *b)
{
    charset_filter_ctx_t *ctx = f->ctx;
    apr_status_t rv;

    APR_BRIGADE_INSERT_TAIL(ctx->tmpbb, b);
    rv = ap_pass_brigade(f->next, ctx->tmpbb);
    if (rv != APR_SUCCESS) {
        ctx->ees = EES_DOWNSTREAM;
    }
    apr_brigade_cleanup(ctx->tmpbb);
    return rv;
}