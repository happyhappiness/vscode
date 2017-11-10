static int BIO_bucket_flush(BIO *bio)
{
    BIO_bucket_t *b = BIO_bucket_ptr(bio);
    apr_bucket *e;

    if (!(b->blen || b->length)) {
        return APR_SUCCESS;
    }

    if (b->blen) {
        e = apr_bucket_transient_create(b->buffer, b->blen,
                                        b->bb->bucket_alloc);
        /* we filled this buffer first so add it to the 
         * head of the brigade
         */
        APR_BRIGADE_INSERT_HEAD(b->bb, e);
        b->blen = 0;
    }

    b->length = 0;
    e = apr_bucket_flush_create(b->bb->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(b->bb, e);

    return ap_pass_brigade(b->frec->pOutputFilter->next, b->bb);
}