    return outctx->rc;
}

/* Just use a simple request.  Any request will work for this, because
 * we use a flag in the conn_rec->conn_vector now.  The fake request just
 * gets the request back to the Apache core so that a response can be sent.
 * Since we use an HTTP/1.x request, we also have to inject the empty line
 * that terminates the headers, or the core will read more data from the
 * socket.
 */
#define HTTP_ON_HTTPS_PORT \
    "GET / HTTP/1.0" CRLF

#define HTTP_ON_HTTPS_PORT_BUCKET(alloc) \
    apr_bucket_immortal_create(HTTP_ON_HTTPS_PORT, \
                               sizeof(HTTP_ON_HTTPS_PORT) - 1, \
                               alloc)

static void ssl_io_filter_disable(SSLConnRec *sslconn,
                                  bio_filter_in_ctx_t *inctx)
{
    SSL_free(inctx->ssl);
    sslconn->ssl = NULL;
    inctx->ssl = NULL;
    inctx->filter_ctx->pssl = NULL;
}

static apr_status_t ssl_io_filter_error(bio_filter_in_ctx_t *inctx,
                                        apr_bucket_brigade *bb,
                                        apr_status_t status)
{
    ap_filter_t *f = inctx->f;
    SSLConnRec *sslconn = myConnConfig(f->c);
    apr_bucket *bucket;
    int send_eos = 1;

    switch (status) {
      case HTTP_BAD_REQUEST:
            /* log the situation */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                         "SSL handshake failed: HTTP spoken on HTTPS port; "
                         "trying to send HTML error page");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, sslconn->server);

            sslconn->non_ssl_request = NON_SSL_SEND_HDR_SEP;
            ssl_io_filter_disable(sslconn, inctx);

            /* fake the request line */
            bucket = HTTP_ON_HTTPS_PORT_BUCKET(f->c->bucket_alloc);
            send_eos = 0;
            break;

      default:
        return status;
    }

    APR_BRIGADE_INSERT_TAIL(bb, bucket);
    if (send_eos) {
        bucket = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, bucket);
    }
    return APR_SUCCESS;
}

static const char ssl_io_filter[] = "SSL/TLS Filter";
static const char ssl_io_buffer[] = "SSL/TLS Buffer";

/*
 *  Close the SSL part of the socket connection
 *  (called immediately _before_ the socket is closed)
 *  or called with
 */
static apr_status_t ssl_filter_io_shutdown(ssl_filter_ctx_t *filter_ctx,
                                           conn_rec *c,
                                           int abortive)
{
    SSL *ssl = filter_ctx->pssl;
    const char *type = "";
    SSLConnRec *sslconn = myConnConfig(c);
    int shutdown_type;

    if (!ssl) {
        return APR_SUCCESS;
    }

    /*
     * Now close the SSL layer of the connection. We've to take
     * the TLSv1 standard into account here:
     *
