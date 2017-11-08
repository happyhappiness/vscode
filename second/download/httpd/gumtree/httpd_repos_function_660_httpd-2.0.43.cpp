static int bio_bucket_write(BIO *bio, const char *in, int inl)
{
    BIO_bucket_t *b = BIO_bucket_ptr(bio);

    /* when handshaking we'll have a small number of bytes.
     * max size SSL will pass us here is about 16k.
     * (16413 bytes to be exact)
     */
    BIO_clear_retry_flags(bio);

    if (!b->length && (inl + b->blen < sizeof(b->buffer))) {
        /* the first two SSL_writes (of 1024 and 261 bytes)
         * need to be in the same packet (vec[0].iov_base)
         */
        /* XXX: could use apr_brigade_write() to make code look cleaner
         * but this way we avoid the malloc(APR_BUCKET_BUFF_SIZE)
         * and free() of it later
         */
        memcpy(&b->buffer[b->blen], in, inl);
        b->blen += inl;
    }
    else {
        /* pass along the encrypted data
         * need to flush since we're using SSL's malloc-ed buffer 
         * which will be overwritten once we leave here
         */
        apr_bucket *bucket = apr_bucket_transient_create(in, inl,
                                                         b->bb->bucket_alloc);

        b->length += inl;
        APR_BRIGADE_INSERT_TAIL(b->bb, bucket);

        BIO_bucket_flush(bio);
    }

    return inl;
}