    if (SSL_is_init_finished(filter_ctx->pssl)) {
        return APR_SUCCESS;
    }

    server = sslconn->server;
    if (sslconn->is_proxy) {
        const char *hostname_note;

        sc = mySrvConfig(server);
        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL Proxy connect failed");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
            return MODSSL_ERROR_BAD_GATEWAY;
        }

        if (sc->proxy_ssl_check_peer_expire != SSL_ENABLED_FALSE) {
            cert = SSL_get_peer_certificate(filter_ctx->pssl);
            if (!cert
                || (X509_cmp_current_time(
                     X509_get_notBefore(cert)) >= 0)
                || (X509_cmp_current_time(
                     X509_get_notAfter(cert)) <= 0)) {
