static brotli_ctx_t *create_ctx(int quality,
                                int lgwin,
                                int lgblock,
                                apr_bucket_alloc_t *alloc,
                                apr_pool_t *pool)
{
    brotli_ctx_t *ctx = apr_pcalloc(pool, sizeof(*ctx));

    ctx->state = BrotliEncoderCreateInstance(alloc_func, free_func, alloc);
    BrotliEncoderSetParameter(ctx->state, BROTLI_PARAM_QUALITY, quality);
    BrotliEncoderSetParameter(ctx->state, BROTLI_PARAM_LGWIN, lgwin);
    BrotliEncoderSetParameter(ctx->state, BROTLI_PARAM_LGBLOCK, lgblock);
    apr_pool_cleanup_register(pool, ctx, cleanup_ctx, apr_pool_cleanup_null);

    ctx->bb = apr_brigade_create(pool, alloc);
    ctx->total_in = 0;
    ctx->total_out = 0;

    return ctx;
}