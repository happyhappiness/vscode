static apr_status_t cleanup_ctx(void *data)
{
    brotli_ctx_t *ctx = data;

    BrotliEncoderDestroyInstance(ctx->state);
    ctx->state = NULL;
    return APR_SUCCESS;
}