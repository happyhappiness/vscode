static int bio_filter_out_write(BIO *bio, const char *in, int inl)
{
    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
    apr_bucket *e;

    /* Abort early if the client has initiated a renegotiation. */
    if (outctx->filter_ctx->config->reneg_state == RENEG_ABORT) {
        outctx->rc = APR_ECONNABORTED;
        return -1;
    }

    /* when handshaking we'll have a small number of bytes.
     * max size SSL will pass us here is about 16k.
     * (16413 bytes to be exact)
     */
    BIO_clear_retry_flags(bio);

    /* Use a transient bucket for the output data - any downstream
     * filter must setaside if necessary. */
    e = apr_bucket_transient_create(in, inl, outctx->bb->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(outctx->bb, e);

    if (bio_filter_out_pass(outctx) < 0) {
        return -1;
    }

    return inl;
}