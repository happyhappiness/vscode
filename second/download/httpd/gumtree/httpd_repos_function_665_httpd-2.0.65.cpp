static int bio_filter_out_write(BIO *bio, const char *in, int inl)
{
    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
    
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

    if (!outctx->length && (inl + outctx->blen < sizeof(outctx->buffer)) &&
        !outctx->filter_ctx->nobuffer) {
        /* the first two SSL_writes (of 1024 and 261 bytes)
         * need to be in the same packet (vec[0].iov_base)
         */
        /* XXX: could use apr_brigade_write() to make code look cleaner
         * but this way we avoid the malloc(APR_BUCKET_BUFF_SIZE)
         * and free() of it later
         */
        memcpy(&outctx->buffer[outctx->blen], in, inl);
        outctx->blen += inl;
    }
    else {
        /* pass along the encrypted data
         * need to flush since we're using SSL's malloc-ed buffer 
         * which will be overwritten once we leave here
         */
        apr_bucket *bucket = apr_bucket_transient_create(in, inl,
                                             outctx->bb->bucket_alloc);

        outctx->length += inl;
        APR_BRIGADE_INSERT_TAIL(outctx->bb, bucket);

        if (bio_filter_out_flush(bio) < 0) {
            return -1;
        }
    }

    return inl;
}