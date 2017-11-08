static int bio_filter_in_read(BIO *bio, char *in, int inlen)
{
    apr_size_t inl = inlen;
    bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)(bio->ptr);
    apr_read_type_e block = inctx->block;
    SSLConnRec *sslconn = myConnConfig(inctx->f->c);

    inctx->rc = APR_SUCCESS;

    /* OpenSSL catches this case, so should we. */
    if (!in)
        return 0;

    /* XXX: flush here only required for SSLv2;
     * OpenSSL calls BIO_flush() at the appropriate times for
     * the other protocols.
     */
    if ((SSL_version(inctx->ssl) == SSL2_VERSION) || sslconn->is_proxy) {
        if (bio_filter_out_flush(inctx->bio_out) < 0) {
            bio_filter_out_ctx_t *outctx =
                   (bio_filter_out_ctx_t *)(inctx->bio_out->ptr);
            inctx->rc = outctx->rc;
            return -1;
        }
    }

    BIO_clear_retry_flags(bio);

    if (!inctx->bb) {
        inctx->rc = APR_EOF;
        return -1;
    }

    if (APR_BRIGADE_EMPTY(inctx->bb)) {

        inctx->rc = ap_get_brigade(inctx->f->next, inctx->bb,
                                   AP_MODE_READBYTES, block,
                                   inl);

        /* If the read returns EAGAIN or success with an empty
         * brigade, return an error after setting the retry flag;
         * SSL_read() will then return -1, and SSL_get_error() will
         * indicate SSL_ERROR_WANT_READ. */
        if (APR_STATUS_IS_EAGAIN(inctx->rc) || APR_STATUS_IS_EINTR(inctx->rc)
               || (inctx->rc == APR_SUCCESS && APR_BRIGADE_EMPTY(inctx->bb))) {
            BIO_set_retry_read(bio);
            return -1;
        }

        if (inctx->rc != APR_SUCCESS) {
            /* Unexpected errors discard the brigade */
            apr_brigade_cleanup(inctx->bb);
            inctx->bb = NULL;
            return -1;
        }
    }

    inctx->rc = brigade_consume(inctx->bb, block, in, &inl);

    if (inctx->rc == APR_SUCCESS) {
        return (int)inl;
    }

    if (APR_STATUS_IS_EAGAIN(inctx->rc)
            || APR_STATUS_IS_EINTR(inctx->rc)) {
        BIO_set_retry_read(bio);
        return (int)inl;
    }

    /* Unexpected errors and APR_EOF clean out the brigade.
     * Subsequent calls will return APR_EOF.
     */
    apr_brigade_cleanup(inctx->bb);
    inctx->bb = NULL;

    if (APR_STATUS_IS_EOF(inctx->rc) && inl) {
        /* Provide the results of this read pass,
         * without resetting the BIO retry_read flag
         */
        return (int)inl;
    }

    return -1;
}