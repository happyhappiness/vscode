static apr_status_t ssl_io_filter_error(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        apr_status_t status)
{
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
            ssl_io_filter_disable(sslconn, f);

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

