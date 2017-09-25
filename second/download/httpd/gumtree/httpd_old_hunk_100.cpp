        apr_size_t bytes = pos - buf;

        bytes += 1;
        value = buf + bytes;
        length = *len - bytes;

        char_buffer_write(&ctx->cbuf, value, length);

        *len = bytes;
    }

    return APR_SUCCESS;
}

/* Just use a simple request.  Any request will work for this, because
 * we use a flag in the conn_rec->conn_vector now.  The fake request just
 * gets the request back to the Apache core so that a response can be sent.
 *
 * We should probably use a 0.9 request, but the BIO bucket code is calling
 * socket_bucket_read one extra time with all 0.9 requests from the client.
 * Until that is resolved, continue to use a 1.0 request, just like we
 * always have.
 */
#define HTTP_ON_HTTPS_PORT \
    "GET / HTTP/1.0"

#define HTTP_ON_HTTPS_PORT_BUCKET(alloc) \
    apr_bucket_immortal_create(HTTP_ON_HTTPS_PORT, \
                               sizeof(HTTP_ON_HTTPS_PORT) - 1, \
                               alloc)

static void ssl_io_filter_disable(ap_filter_t *f)
{
    ssl_io_input_ctx_t *ctx = f->ctx;
    ctx->inbio.ssl = NULL;
    ctx->frec->pssl = NULL;
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
            ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         f->c->base_server,
                         "SSL handshake failed: HTTP spoken on HTTPS port; "
                         "trying to send HTML error page");
            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, f->c->base_server);

            sslconn->non_ssl_request = 1;
            ssl_io_filter_disable(f);

            /* fake the request line */
            bucket = HTTP_ON_HTTPS_PORT_BUCKET(f->c->bucket_alloc);
