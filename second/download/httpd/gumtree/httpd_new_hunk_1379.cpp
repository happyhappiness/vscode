    if (SSL_is_init_finished(filter_ctx->pssl)) {
        return APR_SUCCESS;
    }

    server = sslconn->server;
    if (sslconn->is_proxy) {
#ifndef OPENSSL_NO_TLSEXT
        apr_ipsubnet_t *ip;
#endif
        const char *hostname_note = apr_table_get(c->notes,
                                                  "proxy-request-hostname");
        sc = mySrvConfig(server);

#ifndef OPENSSL_NO_TLSEXT
        /*
         * Enable SNI for backend requests. Make sure we don't do it for
         * pure SSLv2 or SSLv3 connections, and also prevent IP addresses
         * from being included in the SNI extension. (OpenSSL would simply
         * pass them on, but RFC 6066 is quite clear on this: "Literal
         * IPv4 and IPv6 addresses are not permitted".)
         */
        if (hostname_note &&
            sc->proxy->protocol != SSL_PROTOCOL_SSLV2 &&
            sc->proxy->protocol != SSL_PROTOCOL_SSLV3 &&
            apr_ipsubnet_create(&ip, hostname_note, NULL,
                                c->pool) != APR_SUCCESS) {
            if (SSL_set_tlsext_host_name(filter_ctx->pssl, hostname_note)) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                              "SNI extension for SSL Proxy request set to '%s'",
                              hostname_note);
            } else {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
                              "Failed to set SNI extension for SSL Proxy "
                              "request to '%s'", hostname_note);
                ssl_log_ssl_error(APLOG_MARK, APLOG_WARNING, server);
            }
	}
#endif

        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL Proxy connect failed");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
