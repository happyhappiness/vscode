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

