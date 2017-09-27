             * However, this causes failures in perl-framework currently,
             * perhaps pre-test if we have already negotiated?
             */
            SSL_set_state(ssl, SSL_ST_ACCEPT);
            SSL_do_handshake(ssl);

            sslconn->reneg_state = RENEG_REJECT;

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Re-negotiation handshake failed: "
                              "Not accepted by client!?");

                r->connection->aborted = 1;
