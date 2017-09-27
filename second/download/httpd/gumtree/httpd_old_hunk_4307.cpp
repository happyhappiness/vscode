    }

    server = sslconn->server;
    if (sslconn->is_proxy) {
#ifdef HAVE_TLSEXT
        apr_ipsubnet_t *ip;
#endif
        const char *hostname_note = apr_table_get(c->notes,
                                                  "proxy-request-hostname");
        BOOL proxy_ssl_check_peer_ok = TRUE;
        int post_handshake_rc = OK;

        sc = mySrvConfig(server);

#ifdef HAVE_TLSEXT
        /*
         * Enable SNI for backend requests. Make sure we don't do it for
         * pure SSLv3 connections, and also prevent IP addresses
         * from being included in the SNI extension. (OpenSSL would simply
         * pass them on, but RFC 6066 is quite clear on this: "Literal
         * IPv4 and IPv6 addresses are not permitted".)
