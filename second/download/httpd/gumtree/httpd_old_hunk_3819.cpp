         * pure SSLv3 connections, and also prevent IP addresses
         * from being included in the SNI extension. (OpenSSL would simply
         * pass them on, but RFC 6066 is quite clear on this: "Literal
         * IPv4 and IPv6 addresses are not permitted".)
         */
        if (hostname_note &&
            sc->proxy->protocol != SSL_PROTOCOL_SSLV3 &&
            apr_ipsubnet_create(&ip, hostname_note, NULL,
                                c->pool) != APR_SUCCESS) {
            if (SSL_set_tlsext_host_name(filter_ctx->pssl, hostname_note)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                              "SNI extension for SSL Proxy request set to '%s'",
                              hostname_note);
