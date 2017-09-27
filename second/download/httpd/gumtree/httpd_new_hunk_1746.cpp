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

/* Custom apr_status_t error code, used when a plain HTTP request is
 * recevied on an SSL port. */
#define MODSSL_ERROR_HTTP_ON_HTTPS (APR_OS_START_USERERR + 0)

/* Custom apr_status_t error code, used when the proxy cannot
 * establish an outgoing SSL connection. */
#define MODSSL_ERROR_BAD_GATEWAY (APR_OS_START_USERERR + 1)

static void ssl_io_filter_disable(SSLConnRec *sslconn, ap_filter_t *f)
{
    bio_filter_in_ctx_t *inctx = f->ctx;
    SSL_free(inctx->ssl);
    sslconn->ssl = NULL;
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
    case MODSSL_ERROR_HTTP_ON_HTTPS:
            /* log the situation */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                         "SSL handshake failed: HTTP spoken on HTTPS port; "
                         "trying to send HTML error page");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, sslconn->server);

            sslconn->non_ssl_request = 1;
            ssl_io_filter_disable(sslconn, f);

            /* fake the request line */
            bucket = HTTP_ON_HTTPS_PORT_BUCKET(f->c->bucket_alloc);
            break;
            
    case MODSSL_ERROR_BAD_GATEWAY:
        bucket = ap_bucket_error_create(HTTP_BAD_REQUEST, NULL,
                                        f->c->pool, 
                                        f->c->bucket_alloc);
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                      "SSL handshake failed: sending 502");
        break;

    default:
        return status;
    }

    APR_BRIGADE_INSERT_TAIL(bb, bucket);
    bucket = apr_bucket_eos_create(f->c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, bucket);

    return APR_SUCCESS;
}

static const char ssl_io_filter[] = "SSL/TLS Filter";
static const char ssl_io_buffer[] = "SSL/TLS Buffer";

/*
 *  Close the SSL part of the socket connection
 *  (called immediately _before_ the socket is closed)
 *  or called with
 */
static void ssl_filter_io_shutdown(ssl_filter_ctx_t *filter_ctx,
                                   conn_rec *c, int abortive)
{
    SSL *ssl = filter_ctx->pssl;
    const char *type = "";
    SSLConnRec *sslconn = myConnConfig(c);
    int shutdown_type;
    int loglevel = APLOG_DEBUG;

    if (!ssl) {
        return;
    }

    /*
     * Now close the SSL layer of the connection. We've to take
     * the TLSv1 standard into account here:
     *
