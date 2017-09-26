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
            ssl_io_filter_disable(sslconn, f);
