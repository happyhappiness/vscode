    return -1;
}

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

static long bio_filter_out_ctrl(BIO *bio, int cmd, long num, void *ptr)
{
    long ret = 1;
    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);

    switch (cmd) {
    case BIO_CTRL_RESET:
    case BIO_CTRL_EOF:
    case BIO_C_SET_BUF_MEM_EOF_RETURN:
        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, outctx->c,
                      "output bio: unhandled control %d", cmd);
        ret = 0;
        break;
    case BIO_CTRL_WPENDING:
    case BIO_CTRL_PENDING:
    case BIO_CTRL_INFO:
        ret = 0;
        break;
    case BIO_CTRL_GET_CLOSE:
        ret = (long)bio->shutdown;
        break;
      case BIO_CTRL_SET_CLOSE:
        bio->shutdown = (int)num;
        break;
      case BIO_CTRL_FLUSH:
        ret = bio_filter_out_flush(bio);
        break;
      case BIO_CTRL_DUP:
        ret = 1;
        break;
