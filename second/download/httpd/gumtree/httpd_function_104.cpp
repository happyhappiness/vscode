int ssl_hook_process_connection(SSLFilterRec *filter)
{
    conn_rec *c         = (conn_rec *)SSL_get_app_data(filter->pssl);
    SSLConnRec *sslconn = myConnConfig(c);
    SSLSrvConfigRec *sc = mySrvConfig(c->base_server);
    X509 *cert;
    int n, err;
    long verify_result;

    if (!SSL_is_init_finished(filter->pssl)) {
        if (sslconn->is_proxy) {
            if ((n = SSL_connect(filter->pssl)) <= 0) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             c->base_server,
                             "SSL Proxy connect failed");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
                return ssl_abort(filter, c);
            }

            return APR_SUCCESS;
        }

        if ((n = SSL_accept(filter->pssl)) <= 0) {
            err = SSL_get_error(filter->pssl, n);

            if (err == SSL_ERROR_ZERO_RETURN) {
                /*
                 * The case where the connection was closed before any data
                 * was transferred. That's not a real error and can occur
                 * sporadically with some clients.
                 */
                ap_log_error(APLOG_MARK, APLOG_INFO, 0,
                             c->base_server,
                             "SSL handshake stopped: connection was closed");
            }
            else if (err == SSL_ERROR_WANT_READ) {
                /*
                 * This is in addition to what was present earlier. It is 
                 * borrowed from openssl_state_machine.c [mod_tls].
                 * TBD.
                 */
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
            else if ((SSL_get_error(filter->pssl, n) == SSL_ERROR_SYSCALL) &&
                     (errno != EINTR))
            {
                if (errno > 0) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                 c->base_server,
                                 "SSL handshake interrupted by system "
                                 "[Hint: Stop button pressed in browser?!]");
                    ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, 
                                 c->base_server,
                                 "Spurious SSL handshake interrupt [Hint: "
                                 "Usually just one of those OpenSSL "
                                 "confusions!?]");
                    ssl_log_ssl_error(APLOG_MARK, APLOG_INFO, c->base_server);
                }
            }
            else {
                /*
                 * Ok, anything else is a fatal error
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, 
                             c->base_server,
                             "SSL handshake failed (server %s, client %s)",
                             ssl_util_vhostid(c->pool, c->base_server),
                             c->remote_ip ? c->remote_ip : "unknown");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
            }

            return ssl_abort(filter, c);
        }

        /*
         * Check for failed client authentication
         */
        verify_result = SSL_get_verify_result(filter->pssl);

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
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             c->base_server,
                             "SSL client authentication failed, "
                             "accepting certificate based on "
                             "\"SSLVerifyClient optional_no_ca\" "
                             "configuration");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);
            }
            else {
                const char *error = sslconn->verify_error ?
                    sslconn->verify_error :
                    X509_verify_cert_error_string(verify_result);

                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             c->base_server,
                             "SSL client authentication failed: %s",
                             error ? error : "unknown");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, c->base_server);

                return ssl_abort(filter, c);
            }
        }

        /*
         * Remember the peer certificate's DN
         */
        if ((cert = SSL_get_peer_certificate(filter->pssl))) {
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
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                         "No acceptable peer certificate available");

            return ssl_abort(filter, c);
        }
    }

    return APR_SUCCESS;
}