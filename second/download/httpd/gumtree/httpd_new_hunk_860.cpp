{
    buffer->value = in;
    buffer->length = inl;
    return inl;
}

/* This function will read from a brigade and discard the read buckets as it
 * proceeds.  It will read at most *len bytes.
 */
static apr_status_t brigade_consume(apr_bucket_brigade *bb,
                                    apr_read_type_e block,
                                    char *c, apr_size_t *len)
{
    apr_size_t actual = 0;
    apr_status_t status = APR_SUCCESS;
 
    while (!APR_BRIGADE_EMPTY(bb)) {
        apr_bucket *b = APR_BRIGADE_FIRST(bb);
        const char *str;
        apr_size_t str_len;
        apr_size_t consume;

        /* Justin points out this is an http-ism that might
         * not fit if brigade_consume is added to APR.  Perhaps
         * apr_bucket_read(eos_bucket) should return APR_EOF?
         * Then this becomes mainline instead of a one-off.
         */
        if (APR_BUCKET_IS_EOS(b)) {
            status = APR_EOF;
            break;
        }

        /* The reason I'm not offering brigade_consume yet
         * across to apr-util is that the following call
         * illustrates how borked that API really is.  For
         * this sort of case (caller provided buffer) it
         * would be much more trivial for apr_bucket_consume
         * to do all the work that follows, based on the
         * particular characteristics of the bucket we are 
         * consuming here.
         */
        status = apr_bucket_read(b, &str, &str_len, block);
        
        if (status != APR_SUCCESS) {
            if (APR_STATUS_IS_EOF(status)) {
                /* This stream bucket was consumed */
                apr_bucket_delete(b);
                continue;
            }
            break;
        }

        if (str_len > 0) {
            /* Do not block once some data has been consumed */
            block = APR_NONBLOCK_READ;

            /* Assure we don't overflow. */
            consume = (str_len + actual > *len) ? *len - actual : str_len;

            memcpy(c, str, consume);

            c += consume;
            actual += consume;

            if (consume >= b->length) {
                /* This physical bucket was consumed */
                apr_bucket_delete(b);
            }
            else {
                /* Only part of this physical bucket was consumed */
                b->start += consume;
                b->length -= consume;
            }
        }
        else if (b->length == 0) {
            apr_bucket_delete(b);
        }

        /* This could probably be actual == *len, but be safe from stray
         * photons. */
        if (actual >= *len) {
            break;
        }
    }

    *len = actual;
    return status;
}

/*
 * this is the function called by SSL_read()
 */
static int bio_filter_in_read(BIO *bio, char *in, int inl)
{
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

        /* Not a problem, there was simply no data ready yet.
         */
        if (APR_STATUS_IS_EAGAIN(inctx->rc) || APR_STATUS_IS_EINTR(inctx->rc)
               || (inctx->rc == APR_SUCCESS && APR_BRIGADE_EMPTY(inctx->bb))) {
            BIO_set_retry_read(bio);
            return 0;
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
        return inl;
    }

    if (APR_STATUS_IS_EAGAIN(inctx->rc) 
            || APR_STATUS_IS_EINTR(inctx->rc)) {
        BIO_set_retry_read(bio);
        return inl;
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
        return inl;
    }

    return -1;
}


static BIO_METHOD bio_filter_in_method = {
    BIO_TYPE_MEM,
    "APR input filter",
    NULL,                       /* write is never called */
    bio_filter_in_read,
    NULL,                       /* puts is never called */
    NULL,                       /* gets is never called */
    NULL,                       /* ctrl is never called */
    bio_filter_create,
    bio_filter_destroy,
#ifdef OPENSSL_VERSION_NUMBER
    NULL /* sslc does not have the callback_ctrl field */
#endif
};


static apr_status_t ssl_io_input_read(bio_filter_in_ctx_t *inctx,
                                      char *buf,
                                      apr_size_t *len)
{
    apr_size_t wanted = *len;
    apr_size_t bytes = 0;
    int rc;

    *len = 0;

    /* If we have something leftover from last time, try that first. */
    if ((bytes = char_buffer_read(&inctx->cbuf, buf, wanted))) {
        *len = bytes;
        if (inctx->mode == AP_MODE_SPECULATIVE) {
            /* We want to rollback this read. */
            inctx->cbuf.value -= bytes;
            inctx->cbuf.length += bytes;
            return APR_SUCCESS;
        }
        /* This could probably be *len == wanted, but be safe from stray
         * photons.
         */
        if (*len >= wanted) {
            return APR_SUCCESS;
        }
        if (inctx->mode == AP_MODE_GETLINE) {
            if (memchr(buf, APR_ASCII_LF, *len)) {
                return APR_SUCCESS;
            }
        }
        else {
            /* Down to a nonblock pattern as we have some data already
             */
            inctx->block = APR_NONBLOCK_READ;
        }
    }

    while (1) {

        if (!inctx->filter_ctx->pssl) {
            break;
        }

        /* SSL_read may not read because we haven't taken enough data
         * from the stack.  This is where we want to consider all of
         * the blocking and SPECULATIVE semantics
         */
        rc = SSL_read(inctx->filter_ctx->pssl, buf + bytes, wanted - bytes);

        if (rc > 0) {
            *len += rc;
            if (inctx->mode == AP_MODE_SPECULATIVE) {
                /* We want to rollback this read. */
                char_buffer_write(&inctx->cbuf, buf, rc);
            }
            return inctx->rc;
        }
        else if (rc == 0) {
            /* If EAGAIN, we will loop given a blocking read,
             * otherwise consider ourselves at EOF.
             */
            if (APR_STATUS_IS_EAGAIN(inctx->rc)
                    || APR_STATUS_IS_EINTR(inctx->rc)) {
                /* Already read something, return APR_SUCCESS instead. 
                 * On win32 in particular, but perhaps on other kernels,
                 * a blocking call isn't 'always' blocking.
                 */
                if (*len > 0) {
                    inctx->rc = APR_SUCCESS;
                    break;
                }
                if (inctx->block == APR_NONBLOCK_READ) {
                    break;
                }
            }
            else {
                if (*len > 0) {
                    inctx->rc = APR_SUCCESS;
                }
                else {
                    inctx->rc = APR_EOF;
                }
                break;
            }
        }
        else /* (rc < 0) */ {
            int ssl_err = SSL_get_error(inctx->filter_ctx->pssl, rc);
            conn_rec *c = (conn_rec*)SSL_get_app_data(inctx->filter_ctx->pssl);

            if (ssl_err == SSL_ERROR_WANT_READ) {
                /*
                 * If OpenSSL wants to read more, and we were nonblocking,
                 * report as an EAGAIN.  Otherwise loop, pulling more
                 * data from network filter.
                 *
                 * (This is usually the case when the client forces an SSL
                 * renegotation which is handled implicitly by OpenSSL.)
                 */
                inctx->rc = APR_EAGAIN;

                if (*len > 0) {
                    inctx->rc = APR_SUCCESS;
                    break;
                }
                if (inctx->block == APR_NONBLOCK_READ) {
                    break;
                }
                continue;  /* Blocking and nothing yet?  Try again. */
            }
            else if (ssl_err == SSL_ERROR_SYSCALL) {
                if (APR_STATUS_IS_EAGAIN(inctx->rc)
                        || APR_STATUS_IS_EINTR(inctx->rc)) {
                    /* Already read something, return APR_SUCCESS instead. */
                    if (*len > 0) {
                        inctx->rc = APR_SUCCESS;
                        break;
                    }
                    if (inctx->block == APR_NONBLOCK_READ) {
                        break;
                    }
                    continue;  /* Blocking and nothing yet?  Try again. */
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_INFO, inctx->rc, c->base_server,
                                "SSL input filter read failed.");
                }
            }
            else /* if (ssl_err == SSL_ERROR_SSL) */ {
                /*
                 * Log SSL errors and any unexpected conditions.
                 */
                ap_log_error(APLOG_MARK, APLOG_INFO, inctx->rc, c->base_server,
                            "SSL library error %d reading data", ssl_err);
                ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);

            }
            if (inctx->rc == APR_SUCCESS) {
                inctx->rc = APR_EGENERAL;
            }
            break;
        }
    }
    return inctx->rc;
}

static apr_status_t ssl_io_input_getline(bio_filter_in_ctx_t *inctx,
                                         char *buf,
                                         apr_size_t *len)
{
    const char *pos = NULL;
    apr_status_t status;
    apr_size_t tmplen = *len, buflen = *len, offset = 0;
