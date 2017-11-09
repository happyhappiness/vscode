static apr_status_t deflate_ctx_cleanup(void *data)
{
    deflate_ctx *ctx = (deflate_ctx *)data;

    if (ctx)
        ctx->libz_end_func(&ctx->stream);
    return APR_SUCCESS;
}