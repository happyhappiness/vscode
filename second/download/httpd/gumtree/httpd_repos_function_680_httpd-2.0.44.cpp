static void ssl_io_filter_disable(ap_filter_t *f)
{
    bio_filter_in_ctx_t *inctx = f->ctx;
    inctx->ssl = NULL;
    inctx->filter_ctx->pssl = NULL;
}