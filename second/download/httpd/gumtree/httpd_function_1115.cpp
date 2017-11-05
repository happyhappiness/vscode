static int ssl_io_filter_connect(ssl_filter_ctx_t *filter_ctx)
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
        const char *hostname_note;

        sc = mySrvConfig(server);
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
                || (X509_cmp_current_time(
                     X509_get_notBefore(cert)) >= 0)
                || (X509_cmp_current_time(
                     X509_get_notAfter(cert)) <= 0)) {
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                              "SSL Proxy: Peer certificate is expired");
                if (cert) {
                    X509_free(cert);
                }
                /* ensure that the SSL structures etc are freed, etc: */
                ssl_filter_io_shutdown(filter_ctx, c, 1);
                return HTTP_BAD_GATEWAY;
            }
            X509_free(cert);
        }
        if ((sc->proxy_ssl_check_peer_cn == SSL_ENABLED_TRUE)
            && ((hostname_note =
                 apr_table_get(c->notes, "proxy-request-hostname")) != NULL)) {
            const char *hostname;

            hostname = ssl_var_lookup(NULL, server, c, NULL,
                                      "SSL_CLIENT_S_DN_CN");
            apr_table_unset(c->notes, "proxy-request-hostname");
            if (strcasecmp(hostname, hostname_note)) {
                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                              "SSL Proxy: Peer certificate CN mismatch:"
                              " Certificate CN: %s Requested hostname: %s",
                              hostname, hostname_note);
                /* ensure that the SSL structures etc are freed, etc: */
                ssl_filter_io_shutdown(filter_ctx, c, 1);
                return HTTP_BAD_GATEWAY;
            }
        }

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
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                         "SSL handshake stopped: connection was closed");
        }
        else if (ssl_err == SSL_ERROR_WANT_READ) {
            /*
             * This is in addition to what was present earlier. It is
             * borrowed from openssl_state_machine.c [mod_tls].
             * TBD.
             */
            outctx->rc = APR_EAGAIN;
            return SSL_ERROR_WANT_READ;
        }
        else if (ERR_GET_LIB(ERR_peek_error()) == ERR_LIB_SSL &&
                 ERR_GET_REASON(ERR_peek_error()) == SSL_R_HTTP_REQUEST) {
            /*
             * The case where OpenSSL has recognized a HTTP request:
             * This means the client speaks plain HTTP on our HTTPS port.
             * ssl_io_filter_error will disable the ssl filters when it
             * sees this status code.
             */
            return HTTP_BAD_REQUEST;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                          "SSL handshake interrupted by system "
                          "[Hint: Stop button pressed in browser?!]");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
            /*
             * Log SSL errors and any unexpected conditions.
             */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rc, c,
                          "SSL library error %d in handshake "
                          "(server %s)", ssl_err,
                          ssl_util_vhostid(c->pool, server));
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);

        }
        if (inctx->rc == APR_SUCCESS) {
            inctx->rc = APR_EGENERAL;
        }

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
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
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                          "SSL client authentication failed, "
                          "accepting certificate based on "
                          "\"SSLVerifyClient optional_no_ca\" "
                          "configuration");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);
        }
        else {
            const char *error = sslconn->verify_error ?
                sslconn->verify_error :
                X509_verify_cert_error_string(verify_result);

            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                         "SSL client authentication failed: %s",
                         error ? error : "unknown");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, server);

            return ssl_filter_io_shutdown(filter_ctx, c, 1);
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
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, c,
                      "No acceptable peer certificate available");

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
    }

    return APR_SUCCESS;
}