             * handshake to proceed. */
            sslconn->reneg_state = RENEG_ALLOW;

            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02225)
                              "Re-negotiation request failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);

                r->connection->keepalive = AP_CONN_CLOSE;
                return HTTP_FORBIDDEN;
