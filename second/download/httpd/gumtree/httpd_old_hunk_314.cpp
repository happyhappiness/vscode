}

static apr_status_t ssl_io_filter_error(ap_filter_t *f,
                                        apr_bucket_brigade *bb,
                                        apr_status_t status)
{
    apr_bucket *bucket;

    switch (status) {
      case HTTP_BAD_REQUEST:
            /* log the situation */
            ssl_log(f->c->base_server, SSL_LOG_ERROR|SSL_ADD_SSLERR,
                    "SSL handshake failed: HTTP spoken on HTTPS port; "
                    "trying to send HTML error page");

            /* fake the request line */
            bucket = HTTP_ON_HTTPS_PORT_BUCKET(f->c->bucket_alloc);
            ssl_io_filter_disable(f);
            break;

      default:
        return status;
    }

