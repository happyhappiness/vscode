static void ssl_io_filter_disable(ap_filter_t *f)
{
    ssl_io_input_ctx_t *ctx = f->ctx;
    ctx->inbio.ssl = NULL;
    ctx->frec->pssl = NULL;
}