static int bio_filter_out_flush(BIO *bio)
{
    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
    apr_bucket *e;

    AP_DEBUG_ASSERT(APR_BRIGADE_EMPTY(outctx->bb));

    e = apr_bucket_flush_create(outctx->bb->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(outctx->bb, e);

    return bio_filter_out_pass(outctx);
}