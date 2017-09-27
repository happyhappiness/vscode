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
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
