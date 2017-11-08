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