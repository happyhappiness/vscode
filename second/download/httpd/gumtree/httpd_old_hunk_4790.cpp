static apr_status_t ssl_io_filter_error(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        apr_status_t status)
{
    SSLConnRec *sslconn = myConnConfig(f->c);
    apr_bucket *bucket;

    switch (status) {
    case MODSSL_ERROR_HTTP_ON_HTTPS:
            /* log the situation */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c, APLOGNO(01996)
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
