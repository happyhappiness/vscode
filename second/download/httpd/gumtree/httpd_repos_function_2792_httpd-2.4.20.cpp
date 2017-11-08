static apr_status_t flush_output_buffer(sed_filter_ctxt *ctx)
{
    int size = ctx->curoutbuf - ctx->outbuf;
    char *out;
    apr_status_t status = APR_SUCCESS;
    if ((ctx->outbuf == NULL) || (size <=0))
        return status;
    out = apr_pmemdup(ctx->tpool, ctx->outbuf, size);
    status = append_bucket(ctx, out, size);
    ctx->curoutbuf = ctx->outbuf;
    return status;
}