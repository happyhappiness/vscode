        apr_size_t bytes = pos - buf;

        bytes += 1;
        value = buf + bytes;
        length = *len - bytes;

        char_buffer_write(&inctx->cbuf, value, length);

        *len = bytes;
    }

    return APR_SUCCESS;
}


static apr_status_t ssl_filter_write(ap_filter_t *f,
                                     const char *data,
                                     apr_size_t len)
{
    ssl_filter_ctx_t *filter_ctx = f->ctx;
    bio_filter_out_ctx_t *outctx = 
           (bio_filter_out_ctx_t *)(filter_ctx->pbioWrite->ptr);
    int res;

    /* write SSL */
    if (filter_ctx->pssl == NULL) {
        return APR_EGENERAL;
    }

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
            ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
                        "SSL output filter write failed.");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
            /*
             * Log SSL errors
             */
            ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
                         "SSL library error %d writing data", ssl_err);
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
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

        ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
                     "failed to write %d of %d bytes (%s)",
                     len - (apr_size_t)res, len, reason);

        outctx->rc = APR_EGENERAL;
    }
    return outctx->rc;
}

/* Just use a simple request.  Any request will work for this, because
 * we use a flag in the conn_rec->conn_vector now.  The fake request just
 * gets the request back to the Apache core so that a response can be sent.
 *
 * To avoid calling back for more data from the socket, use an HTTP/0.9
 * request, and tack on an EOS bucket.
 */
#define HTTP_ON_HTTPS_PORT \
    "GET /" CRLF

#define HTTP_ON_HTTPS_PORT_BUCKET(alloc) \
    apr_bucket_immortal_create(HTTP_ON_HTTPS_PORT, \
                               sizeof(HTTP_ON_HTTPS_PORT) - 1, \
                               alloc)

static void ssl_io_filter_disable(ap_filter_t *f)
{
    bio_filter_in_ctx_t *inctx = f->ctx;
    inctx->ssl = NULL;
    inctx->filter_ctx->pssl = NULL;
}

static apr_status_t ssl_io_filter_error(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        apr_status_t status)
{
    SSLConnRec *sslconn = myConnConfig(f->c);
    apr_bucket *bucket;

    switch (status) {
      case HTTP_BAD_REQUEST:
            /* log the situation */
            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         f->c->base_server,
                         "SSL handshake failed: HTTP spoken on HTTPS port; "
                         "trying to send HTML error page");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, f->c->base_server);

            sslconn->non_ssl_request = 1;
            ssl_io_filter_disable(f);

            /* fake the request line */
            bucket = HTTP_ON_HTTPS_PORT_BUCKET(f->c->bucket_alloc);
