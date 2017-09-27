    }

    server = sslconn->server;
    if (sslconn->is_proxy) {
#ifdef HAVE_TLSEXT
        apr_ipsubnet_t *ip;
#ifdef HAVE_TLS_ALPN
        const char *alpn_note;
#endif
#endif
        const char *hostname_note = apr_table_get(c->notes,
                                                  "proxy-request-hostname");
        BOOL proxy_ssl_check_peer_ok = TRUE;
        int post_handshake_rc = OK;

        sc = mySrvConfig(server);

#ifdef HAVE_TLSEXT
#ifdef HAVE_TLS_ALPN
        alpn_note = apr_table_get(c->notes, "proxy-request-alpn-protos");
        if (alpn_note) {
            char *protos, *s, *p, *last;
            apr_size_t len;

            s = protos = apr_pcalloc(c->pool, strlen(alpn_note)+1);
            p = apr_pstrdup(c->pool, alpn_note);
            while ((p = apr_strtok(p, ", ", &last))) {
                len = last - p - (*last? 1 : 0); 
                if (len > 255) {
                    ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(03309)
                                  "ALPN proxy protocol identifier too long: %s",
                                  p);
                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, server);
                    return APR_EGENERAL;
                }
                *s++ = (unsigned char)len;
                while (len--) {
                    *s++ = *p++;
                }
                p = NULL;
            }
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                          "setting alpn protos from '%s', protolen=%d", 
                          alpn_note, (int)(s - protos));
            if (protos != s && SSL_set_alpn_protos(filter_ctx->pssl, 
                                                   (unsigned char *)protos, 
                                                   s - protos)) {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c, APLOGNO(03310)
                              "error setting alpn protos from '%s'", alpn_note);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_WARNING, server);
            }
        }
#endif /* defined HAVE_TLS_ALPN */
        /*
         * Enable SNI for backend requests. Make sure we don't do it for
         * pure SSLv3 connections, and also prevent IP addresses
         * from being included in the SNI extension. (OpenSSL would simply
         * pass them on, but RFC 6066 is quite clear on this: "Literal
         * IPv4 and IPv6 addresses are not permitted".)
