static apr_status_t ssl_filter_write(ap_filter_t *f,
                                     const char *data,
                                     apr_size_t len)
{
    ssl_filter_ctx_t *filter_ctx = f->ctx;
    bio_filter_out_ctx_t *outctx;
    int res;

    /* write SSL */
    if (filter_ctx->pssl == NULL) {
        return APR_EGENERAL;
    }

    outctx = (bio_filter_out_ctx_t *)filter_ctx->pbioWrite->ptr;
    res = SSL_write(filter_ctx->pssl, (unsigned char *)data, len);

    if (res < 0) {
        int ssl_err = SSL_get_error(filter_ctx->pssl, res);
        conn_rec *c = (conn_rec*)SSL_get_app_data(outctx->filter_ctx->pssl);

        if (ssl_err == SSL_ERROR_WANT_WRITE) {
            /*
             * If OpenSSL wants to write more, and we were nonblocking,
             * report as an EAGAIN.  Otherwise loop, pushing more
             * data at the network filter.
             *
             * (This is usually the case when the client forces an SSL
             * renegotation which is handled implicitly by OpenSSL.)
             */
            outctx->rc = APR_EAGAIN;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
                          "SSL output filter write failed.");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
            /*
             * Log SSL errors
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
                          "SSL library error %d writing data", ssl_err);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, mySrvFromConn(c));
        }
        if (outctx->rc == APR_SUCCESS) {
            outctx->rc = APR_EGENERAL;
        }
    }
    else if ((apr_size_t)res != len) {
        conn_rec *c = f->c;
        char *reason = "reason unknown";

        /* XXX: probably a better way to determine this */
        if (SSL_total_renegotiations(filter_ctx->pssl)) {
            reason = "likely due to failed renegotiation";
        }

        ap_log_cerror(APLOG_MARK, APLOG_INFO, outctx->rc, c,
                      "failed to write %" APR_SSIZE_T_FMT
                      " of %" APR_SIZE_T_FMT " bytes (%s)",
                      len - (apr_size_t)res, len, reason);

        outctx->rc = APR_EGENERAL;
    }
    return outctx->rc;
}