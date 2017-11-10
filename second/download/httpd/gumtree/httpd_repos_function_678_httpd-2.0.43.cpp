static void ssl_io_input_add_filter(SSLFilterRec *frec, conn_rec *c,
                                    SSL *ssl)
{
    ssl_io_input_ctx_t *ctx;

    ctx = apr_palloc(c->pool, sizeof(*ctx));

    frec->pInputFilter = ap_add_input_filter(ssl_io_filter, ctx, NULL, c);

    frec->pbioRead = BIO_new(BIO_s_in_bucket());
    frec->pbioRead->ptr = (void *)&ctx->inbio;

    ctx->frec = frec;
    ctx->inbio.ssl = ssl;
    ctx->inbio.wbio = frec->pbioWrite;
    ctx->inbio.f = frec->pInputFilter;
    ctx->inbio.bb = apr_brigade_create(c->pool, c->bucket_alloc);
    ctx->inbio.bucket = NULL;
    ctx->inbio.cbuf.length = 0;

    ctx->cbuf.length = 0;

    ctx->pool = c->pool;
}