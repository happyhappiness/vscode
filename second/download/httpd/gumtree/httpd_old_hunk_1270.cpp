        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL Proxy connect failed");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
            return HTTP_BAD_GATEWAY;
        }

        if (sc->proxy_ssl_check_peer_expire == SSL_ENABLED_TRUE) {
            cert = SSL_get_peer_certificate(filter_ctx->pssl);
            if (!cert
