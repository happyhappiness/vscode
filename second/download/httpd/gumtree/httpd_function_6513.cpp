static apr_status_t ssl_io_filter_handshake(ssl_filter_ctx_t *filter_ctx)
{
    conn_rec *c         = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
    SSLConnRec *sslconn = myConnConfig(c);
    SSLSrvConfigRec *sc;
    X509 *cert;
    int n;
    int ssl_err;
    long verify_result;
    server_rec *server;

    if (SSL_is_init_finished(filter_ctx->pssl)) {
        return APR_SUCCESS;
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
         */
        if (hostname_note &&
#ifndef OPENSSL_NO_SSL3
            sc->proxy->protocol != SSL_PROTOCOL_SSLV3 &&
#endif
            apr_ipsubnet_create(&ip, hostname_note, NULL,
                                c->pool) != APR_SUCCESS) {
            if (SSL_set_tlsext_host_name(filter_ctx->pssl, hostname_note)) {
                ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, c,
                              "SNI extension for SSL Proxy request set to '%s'",
                              hostname_note);
            } else {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c, APLOGNO(02002)
                              "Failed to set SNI extension for SSL Proxy "
                              "request to '%s'", hostname_note);
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_WARNING, server);
            }
        }
#endif

        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02003)
                          "SSL Proxy connect failed");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
            apr_table_setn(c->notes, "SSL_connect_rv", "err");
            return MODSSL_ERROR_BAD_GATEWAY;
        }

        cert = SSL_get_peer_certificate(filter_ctx->pssl);

        if (sc->proxy_ssl_check_peer_expire != SSL_ENABLED_FALSE) {
            if (!cert
                || (X509_cmp_current_time(
                     X509_get_notBefore(cert)) >= 0)
                || (X509_cmp_current_time(
                     X509_get_notAfter(cert)) <= 0)) {
                proxy_ssl_check_peer_ok = FALSE;
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02004)
                              "SSL Proxy: Peer certificate is expired");
            }
        }
        if ((sc->proxy_ssl_check_peer_name != SSL_ENABLED_FALSE) &&
            ((sc->proxy_ssl_check_peer_cn != SSL_ENABLED_FALSE) ||
             (sc->proxy_ssl_check_peer_name == SSL_ENABLED_TRUE)) &&
            hostname_note) {
            apr_table_unset(c->notes, "proxy-request-hostname");
            if (!cert
                || modssl_X509_match_name(c->pool, cert, hostname_note,
                                          TRUE, server) == FALSE) {
                proxy_ssl_check_peer_ok = FALSE;
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02411)
                              "SSL Proxy: Peer certificate does not match "
                              "for hostname %s", hostname_note);
            }
        }
        else if ((sc->proxy_ssl_check_peer_cn == SSL_ENABLED_TRUE) &&
            hostname_note) {
            const char *hostname;
            int match = 0;

            hostname = ssl_var_lookup(NULL, server, c, NULL,
                                      "SSL_CLIENT_S_DN_CN");
            apr_table_unset(c->notes, "proxy-request-hostname");

            /* Do string match or simplest wildcard match if that
             * fails. */
            match = strcasecmp(hostname, hostname_note) == 0;
            if (!match && strncmp(hostname, "*.", 2) == 0) {
                const char *p = ap_strchr_c(hostname_note, '.');
                
                match = p && strcasecmp(p, hostname + 1) == 0;
            }

            if (!match) {
                proxy_ssl_check_peer_ok = FALSE;
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02005)
                              "SSL Proxy: Peer certificate CN mismatch:"
                              " Certificate CN: %s Requested hostname: %s",
                              hostname, hostname_note);
            }
        }

        if (proxy_ssl_check_peer_ok == TRUE) {
            /* another chance to fail */
            post_handshake_rc = ssl_run_proxy_post_handshake(c, filter_ctx->pssl);
        }

        if (cert) {
            X509_free(cert);
        }

        if (proxy_ssl_check_peer_ok != TRUE
            || (post_handshake_rc != OK && post_handshake_rc != DECLINED)) {
            /* ensure that the SSL structures etc are freed, etc: */
            ssl_filter_io_shutdown(filter_ctx, c, 1);
            apr_table_setn(c->notes, "SSL_connect_rv", "err");
            return HTTP_BAD_GATEWAY;
        }

        apr_table_setn(c->notes, "SSL_connect_rv", "ok");
        return APR_SUCCESS;
    }

    if ((n = SSL_accept(filter_ctx->pssl)) <= 0) {
        bio_filter_in_ctx_t *inctx = (bio_filter_in_ctx_t *)
                                     (filter_ctx->pbioRead->ptr);
        bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)
                                       (filter_ctx->pbioWrite->ptr);
        apr_status_t rc = inctx->rc ? inctx->rc : outctx->rc ;
        ssl_err = SSL_get_error(filter_ctx->pssl, n);

        if (ssl_err == SSL_ERROR_ZERO_RETURN) {
            /*
             * The case where the connection was closed before any data
             * was transferred. That's not a real error and can occur
             * sporadically with some clients.
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c, APLOGNO(02006)
                         "SSL handshake stopped: connection was closed");
        }
        else if (ssl_err == SSL_ERROR_WANT_READ) {
            /*
             * This is in addition to what was present earlier. It is
             * borrowed from openssl_state_machine.c [mod_tls].
             * TBD.
             */
            outctx->rc = APR_EAGAIN;
            return APR_EAGAIN;
        }
        else if (ERR_GET_LIB(ERR_peek_error()) == ERR_LIB_SSL &&
                 ERR_GET_REASON(ERR_peek_error()) == SSL_R_HTTP_REQUEST) {
            /*
             * The case where OpenSSL has recognized a HTTP request:
             * This means the client speaks plain HTTP on our HTTPS port.
             * ssl_io_filter_error will disable the ssl filters when it
             * sees this status code.
             */
            return MODSSL_ERROR_HTTP_ON_HTTPS;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, rc, c, APLOGNO(02007)
                          "SSL handshake interrupted by system "
                          "[Hint: Stop button pressed in browser?!]");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
            /*
             * Log SSL errors and any unexpected conditions.
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c, APLOGNO(02008)
                          "SSL library error %d in handshake "
                          "(server %s)", ssl_err,
                          ssl_util_vhostid(c->pool, server));
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);

        }
        if (inctx->rc == APR_SUCCESS) {
            inctx->rc = APR_EGENERAL;
        }

        ssl_filter_io_shutdown(filter_ctx, c, 1);
        return inctx->rc;
    }
    sc = mySrvConfig(sslconn->server);

    /*
     * Check for failed client authentication
     */
    verify_result = SSL_get_verify_result(filter_ctx->pssl);

    if ((verify_result != X509_V_OK) ||
        sslconn->verify_error)
    {
        if (ssl_verify_error_is_optional(verify_result) &&
            (sc->server->auth.verify_mode == SSL_CVERIFY_OPTIONAL_NO_CA))
        {
            /* leaving this log message as an error for the moment,
             * according to the mod_ssl docs:
             * "level optional_no_ca is actually against the idea
             *  of authentication (but can be used to establish
             * SSL test pages, etc.)"
             * optional_no_ca doesn't appear to work as advertised
             * in 1.x
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02009)
                          "SSL client authentication failed, "
                          "accepting certificate based on "
                          "\"SSLVerifyClient optional_no_ca\" "
                          "configuration");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);
        }
        else {
            const char *error = sslconn->verify_error ?
                sslconn->verify_error :
                X509_verify_cert_error_string(verify_result);

            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02010)
                         "SSL client authentication failed: %s",
                         error ? error : "unknown");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_INFO, server);

            ssl_filter_io_shutdown(filter_ctx, c, 1);
            return APR_ECONNABORTED;
        }
    }

    /*
     * Remember the peer certificate's DN
     */
    if ((cert = SSL_get_peer_certificate(filter_ctx->pssl))) {
        if (sslconn->client_cert) {
            X509_free(sslconn->client_cert);
        }
        sslconn->client_cert = cert;
        sslconn->client_dn = NULL;
    }

    /*
     * Make really sure that when a peer certificate
     * is required we really got one... (be paranoid)
     */
    if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
        !sslconn->client_cert)
    {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c, APLOGNO(02011)
                      "No acceptable peer certificate available");

        ssl_filter_io_shutdown(filter_ctx, c, 1);
        return APR_ECONNABORTED;
    }

    return APR_SUCCESS;
}