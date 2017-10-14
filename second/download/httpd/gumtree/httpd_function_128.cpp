static int ssl_io_filter_connect(ssl_filter_ctx_t *filter_ctx)
{
    conn_rec *c         = (conn_rec *)SSL_get_app_data(filter_ctx->pssl);
    SSLConnRec *sslconn = myConnConfig(c);
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
    X509 *cert;
    int n;
    int ssl_err;
    long verify_result;

    if (SSL_is_init_finished(filter_ctx->pssl)) {
        return APR_SUCCESS;
    }

    if (sslconn->is_proxy) {
        if ((n = SSL_connect(filter_ctx->pssl)) <= 0) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL Proxy connect failed");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
            return ssl_filter_io_shutdown(filter_ctx, c, 1);
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
            ap_log_error(APLOG_MARK, APLOG_INFO, rc,
                         c->base_server,
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
        else if (ERR_GET_REASON(ERR_peek_error()) == SSL_R_HTTP_REQUEST) {
            /*
             * The case where OpenSSL has recognized a HTTP request:
             * This means the client speaks plain HTTP on our HTTPS port.
             * ssl_io_filter_error will disable the ssl filters when it
             * sees this status code.
             */
            return HTTP_BAD_REQUEST;
        }
        else if (ssl_err == SSL_ERROR_SYSCALL) {
            ap_log_error(APLOG_MARK, APLOG_INFO, rc, c->base_server,
                         "SSL handshake interrupted by system "
                         "[Hint: Stop button pressed in browser?!]");
        }
        else /* if (ssl_err == SSL_ERROR_SSL) */ {
            /*
             * Log SSL errors and any unexpected conditions.
             */
            ap_log_error(APLOG_MARK, APLOG_INFO, rc, c->base_server,
                         "SSL library error %d in handshake "
                         "(server %s, client %s)", ssl_err,
                         ssl_util_vhostid(c->pool, c->base_server),
                         c->remote_ip ? c->remote_ip : "unknown");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);

        }
        if (inctx->rc == APR_SUCCESS) {
            inctx->rc = APR_EGENERAL;
        }

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
    }

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
            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL client authentication failed, "
                         "accepting certificate based on "
                         "\"SSLVerifyClient optional_no_ca\" "
                         "configuration");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
        }
        else {
            const char *error = sslconn->verify_error ?
                sslconn->verify_error :
                X509_verify_cert_error_string(verify_result);

            ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                         c->base_server,
                         "SSL client authentication failed: %s",
                         error ? error : "unknown");
            ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);

            return ssl_filter_io_shutdown(filter_ctx, c, 1);
        }
    }

    /*
     * Remember the peer certificate's DN
     */
    if ((cert = SSL_get_peer_certificate(filter_ctx->pssl))) {
        sslconn->client_cert = cert;
        sslconn->client_dn = NULL;
        X509_free(cert);
    }

    /*
     * Make really sure that when a peer certificate
     * is required we really got one... (be paranoid)
     */
    if ((sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE) &&
        !sslconn->client_cert)
    {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, c->base_server,
                     "No acceptable peer certificate available");

        return ssl_filter_io_shutdown(filter_ctx, c, 1);
    }

    return APR_SUCCESS;
}