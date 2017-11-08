static int bio_filter_out_write(BIO *bio, const char *in, int inl)
{
    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
    apr_bucket *e;
    int need_flush;

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

    /* In theory, OpenSSL should flush as necessary, but it is known
     * not to do so correctly in some cases (< 0.9.8m; see PR 46952),
     * or on the proxy/client side (after ssl23_client_hello(), e.g.
     * ssl/proxy.t test suite).
     *
     * Historically, this flush call was performed only for an SSLv2
     * connection or for a proxy connection.  Calling _out_flush can
     * be expensive in cases where requests/reponses are pipelined,
     * so limit the performance impact to handshake time.
     */
#if OPENSSL_VERSION_NUMBER < 0x0009080df
     need_flush = !SSL_is_init_finished(outctx->filter_ctx->pssl)
#else
     need_flush = SSL_in_connect_init(outctx->filter_ctx->pssl);
#endif
    if (need_flush) {
        e = apr_bucket_flush_create(outctx->bb->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(outctx->bb, e);
    }

    if (bio_filter_out_pass(outctx) < 0) {
        return -1;
    }

    return inl;
}