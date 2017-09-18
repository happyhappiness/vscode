{
    buffer->value = in;
    buffer->length = inl;
    return inl;
}

/*
 * this is the function called by SSL_read()
 */
#define BIO_bucket_in_ptr(bio) (BIO_bucket_in_t *)bio->ptr

static int bio_bucket_in_read(BIO *bio, char *in, int inl)
{
    BIO_bucket_in_t *inbio = BIO_bucket_in_ptr(bio);
    SSLConnRec *sslconn = myConnConfig(inbio->f->c);
    int len = 0;

    /* XXX: flush here only required for SSLv2;
     * OpenSSL calls BIO_flush() at the appropriate times for
     * the other protocols.
     */
    if ((SSL_version(inbio->ssl) == SSL2_VERSION) || sslconn->is_proxy) {
        BIO_bucket_flush(inbio->wbio);
    }

    inbio->rc = APR_SUCCESS;
    
    /* first use data already read from socket if any */
    if ((len = char_buffer_read(&inbio->cbuf, in, inl))) {
        if ((len <= inl) || inbio->mode == AP_MODE_GETLINE) {
            return len;
        }
        inl -= len;
    }

    while (1) {
        const char *buf;
        apr_size_t buf_len = 0;

        if (inbio->bucket) {
            /* all of the data in this bucket has been read,
             * so we can delete it now.
             */
            apr_bucket_delete(inbio->bucket);
            inbio->bucket = NULL;
        }

        if (APR_BRIGADE_EMPTY(inbio->bb)) {
            /* We will always call with READBYTES even if the user wants
             * GETLINE.
             */
            inbio->rc = ap_get_brigade(inbio->f->next, inbio->bb,
                                       AP_MODE_READBYTES, inbio->block, 
                                       inl);

            if ((inbio->rc != APR_SUCCESS) || APR_BRIGADE_EMPTY(inbio->bb))
            {
                break;
            }
        }

        inbio->bucket = APR_BRIGADE_FIRST(inbio->bb);

        inbio->rc = apr_bucket_read(inbio->bucket,
                                    &buf, &buf_len, inbio->block);

        if (inbio->rc != APR_SUCCESS) {
            apr_bucket_delete(inbio->bucket);
            inbio->bucket = NULL;
            return len;
        }

        if (buf_len) {
            /* Protected against len > MAX_INT 
             */
            if ((len + (int)buf_len) >= inl || (int)buf_len < 0) {
                /* we have enough to fill the buffer.
                 * append if we have already written to the buffer.
                 */
                int nibble = inl - len;
                char *value = (char *)buf+nibble;

                int length = buf_len - nibble;
                memcpy(in + len, buf, nibble);

                char_buffer_write(&inbio->cbuf, value, length);
                len += nibble;

                break;
            }
            else {
                /* not enough data,
                 * save what we have and try to read more.
                 */
                memcpy(in + len, buf, buf_len);
                len += buf_len;
            }
        }

        if (inbio->mode == AP_MODE_GETLINE) {
            /* only read from the socket once in getline mode.
             * since callers buffer size is likely much larger than
             * the request headers.  caller can always come back for more
             * if first read didn't get all the headers.
             */
            break;
        }
    }

    return len;
}

static BIO_METHOD bio_bucket_in_method = {
    BIO_TYPE_MEM,
    "APR input bucket brigade",
    NULL,                       /* write is never called */
    bio_bucket_in_read,
    NULL,                       /* puts is never called */
    NULL,                       /* gets is never called */
    NULL,                       /* ctrl is never called */
    bio_bucket_new,
    bio_bucket_free,
#ifdef OPENSSL_VERSION_NUMBER
    NULL /* sslc does not have the callback_ctrl field */
#endif
};

static BIO_METHOD *BIO_s_in_bucket(void)
{
    return &bio_bucket_in_method;
}

static const char ssl_io_filter[] = "SSL/TLS Filter";

static int ssl_io_hook_read(SSL *ssl, char *buf, int len)
{
    int rc;

    if (ssl == NULL) {
        return -1;
    }

    rc = SSL_read(ssl, buf, len);

    if (rc <= 0) {
        int ssl_err = SSL_get_error(ssl, rc);

        if (ssl_err == SSL_ERROR_WANT_READ) {
            /*
             * Simulate an EINTR in case OpenSSL wants to read more.
             * (This is usually the case when the client forces an SSL
             * renegotation which is handled implicitly by OpenSSL.)
             */
            errno = EINTR;
            rc = 0; /* non fatal error */
        }
        else if (ssl_err == SSL_ERROR_SSL) {
            /*
             * Log SSL errors
             */
            conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                    "SSL error on reading data");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
        }
    }

    return rc;
}

static int ssl_io_hook_write(SSL *ssl, unsigned char *buf, int len)
{
    int rc;

    if (ssl == NULL) {
        return -1;
    }

    rc = SSL_write(ssl, buf, len);

    if (rc < 0) {
        int ssl_err = SSL_get_error(ssl, rc);

        if (ssl_err == SSL_ERROR_WANT_WRITE) {
            /*
             * Simulate an EINTR in case OpenSSL wants to write more.
             */
            errno = EINTR;
        }
        else if (ssl_err == SSL_ERROR_SSL) {
            /*
             * Log SSL errors
             */
            conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                    "SSL error on writing data");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
        }
        /*
         * XXX - Just trying to reflect the behaviour in 
         * openssl_state_machine.c [mod_tls]. TBD
         */
        rc = 0;
    }
    return rc;
}

static apr_status_t ssl_filter_write(ap_filter_t *f,
                                     const char *data,
                                     apr_size_t len)
{
    SSLFilterRec *ctx = f->ctx;
    apr_size_t n;

    /* write SSL */
    n = ssl_io_hook_write(ctx->pssl, (unsigned char *)data, len);

    if (n != len) {
        conn_rec *c = f->c;
        char *reason = "reason unknown";

        /* XXX: probably a better way to determine this */
        if (SSL_total_renegotiations(ctx->pssl)) {
            reason = "likely due to failed renegotiation";
        }

        ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                "failed to write %d of %d bytes (%s)",
                n > 0 ? len - n : len, len, reason);

        return APR_EINVAL;
    }

    return APR_SUCCESS;
}

static apr_status_t ssl_io_filter_Output(ap_filter_t *f,
                                         apr_bucket_brigade *bb)
{
    apr_status_t status = APR_SUCCESS;
    SSLFilterRec *ctx = f->ctx;

    if (!ctx->pssl) {
        /* ssl_abort() has been called */
        return ap_pass_brigade(f->next, bb);
    }

    if ((status = ssl_hook_process_connection(ctx)) != APR_SUCCESS) {
        return status;
    }

    while (!APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *bucket = APR_BRIGADE_FIRST(bb);

        /* If it is a flush or EOS, we need to pass this down. 
         * These types do not require translation by OpenSSL.  
         */
        if (APR_BUCKET_IS_EOS(bucket) || APR_BUCKET_IS_FLUSH(bucket)) {
            if ((status = BIO_bucket_flush(ctx->pbioWrite)) != APR_SUCCESS) {
                return status;
            }

            if (APR_BUCKET_IS_EOS(bucket)) {
                /* By definition, nothing can come after EOS.
                 * which also means we can pass the rest of this brigade
                 * without creating a new one since it only contains the
                 * EOS bucket.
                 */

                if ((status = ap_pass_brigade(f->next, bb)) != APR_SUCCESS) {
                    return status;
                }
                break;
            }
            else {
                /* BIO_bucket_flush() already passed down a flush bucket
                 * if there was any data to be flushed.
                 */
                apr_bucket_delete(bucket);
            }
        }
        else {
            /* read filter */
            const char *data;
            apr_size_t len;

            apr_bucket_read(bucket, &data, &len, APR_BLOCK_READ);
            status = ssl_filter_write(f, data, len);
            apr_bucket_delete(bucket);

            if (status != APR_SUCCESS) {
                break;
            }
        }
    }

    return status;
}

/*
 * ctx->cbuf is leftover plaintext from ssl_io_input_getline,
 * use what we have there first if any,
 * then go for more by calling ssl_io_hook_read.
 */
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

static apr_status_t ssl_io_input_getline(ssl_io_input_ctx_t *ctx,
                                         char *buf,
                                         apr_size_t *len)
{
    const char *pos = NULL;
    apr_status_t status;
    apr_size_t tmplen = *len, buflen = *len, offset = 0;
