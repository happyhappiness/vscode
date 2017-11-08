static int bio_filter_out_flush(BIO *bio)
{
    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
    apr_bucket *e;

    if (!(outctx->blen || outctx->length)) {
        outctx->rc = APR_SUCCESS;
        return 1;
    }

    if (outctx->blen) {
        e = apr_bucket_transient_create(outctx->buffer, outctx->blen,
                                        outctx->bb->bucket_alloc);
        /* we filled this buffer first so add it to the 
         * head of the brigade
         */
        APR_BRIGADE_INSERT_HEAD(outctx->bb, e);
        outctx->blen = 0;
    }

    outctx->length = 0;
    e = apr_bucket_flush_create(outctx->bb->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(outctx->bb, e);

    outctx->rc = ap_pass_brigade(outctx->filter_ctx->pOutputFilter->next,
                                 outctx->bb);
    /* Fail if the connection was reset: */
    if (outctx->rc == APR_SUCCESS && outctx->c->aborted) {
        outctx->rc = APR_ECONNRESET;
    }
    return (outctx->rc == APR_SUCCESS) ? 1 : -1;
}