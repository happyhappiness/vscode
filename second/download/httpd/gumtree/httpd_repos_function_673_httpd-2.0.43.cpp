static apr_status_t ssl_io_input_read(ssl_io_input_ctx_t *ctx,
                                      char *buf,
                                      apr_size_t *len)
{
    apr_size_t wanted = *len;
    apr_size_t bytes = 0;
    int rc;

    *len = 0;

    if ((bytes = char_buffer_read(&ctx->cbuf, buf, wanted))) {
        *len = bytes;
        if (ctx->inbio.mode == AP_MODE_SPECULATIVE) {
            /* We want to rollback this read. */
            ctx->cbuf.value -= bytes;
            ctx->cbuf.length += bytes;
            return APR_SUCCESS;
        } 
        if ((*len >= wanted) || ctx->inbio.mode == AP_MODE_GETLINE) {
            return APR_SUCCESS;
        }
    }

    rc = ssl_io_hook_read(ctx->frec->pssl, buf + bytes, wanted - bytes);

    if (rc > 0) {
        *len += rc;
        if (ctx->inbio.mode == AP_MODE_SPECULATIVE) {
            char_buffer_write(&ctx->cbuf, buf, rc);
        }
    }
    else if ((rc == 0) && (errno != EINTR)) {
        /* something other than SSL_ERROR_WANT_READ */
        return APR_EOF;
    }
    else if ((rc == -1) && (ctx->inbio.rc == APR_SUCCESS)) {
        /*
         * bucket read from socket was successful,
         * but there was an error within the ssl runtime.
         */
        return APR_EGENERAL;
    }

    return ctx->inbio.rc;
}