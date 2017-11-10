static void ssl_io_input_add_filter(ssl_filter_ctx_t *filter_ctx, conn_rec *c,
                                    SSL *ssl)
{
    bio_filter_in_ctx_t *inctx;

    inctx = apr_palloc(c->pool, sizeof(*inctx));

    filter_ctx->pInputFilter = ap_add_input_filter(ssl_io_filter, inctx, NULL, c);

    filter_ctx->pbioRead = BIO_new(&bio_filter_in_method);
    filter_ctx->pbioRead->ptr = (void *)inctx;

    inctx->ssl = ssl;
    inctx->bio_out = filter_ctx->pbioWrite;
    inctx->f = filter_ctx->pInputFilter;
    inctx->rc = APR_SUCCESS;
    inctx->mode = AP_MODE_READBYTES;
    inctx->cbuf.length = 0;
    inctx->bb = apr_brigade_create(c->pool, c->bucket_alloc);
    inctx->block = APR_BLOCK_READ;
    inctx->pool = c->pool;
    inctx->filter_ctx = filter_ctx;
}