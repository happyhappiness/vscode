            }
        }
        else {
            request_rec *id = r->main ? r->main : r;

            /* do a full renegotiation */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Performing full renegotiation: "
                         "complete handshake protocol");

            SSL_set_session_id_context(ssl,
                                       (unsigned char *)&id,
                                       sizeof(id));

            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation request failed");

                r->connection->aborted = 1;
                return HTTP_FORBIDDEN;
            }

            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "Awaiting re-negotiation handshake");

            /* XXX: Should replace SSL_set_state with SSL_renegotiate(ssl);
             * However, this causes failures in perl-framework currently,
             * perhaps pre-test if we have already negotiated?
             */
            SSL_set_state(ssl, SSL_ST_ACCEPT);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation handshake failed: "
                        "Not accepted by client!?");

                r->connection->aborted = 1;
                return HTTP_FORBIDDEN;
            }
        }

