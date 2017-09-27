            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Re-negotiation request failed");
                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, r->server);

                r->connection->aborted = 1;
                return HTTP_FORBIDDEN;
            }

            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "Awaiting re-negotiation handshake");

