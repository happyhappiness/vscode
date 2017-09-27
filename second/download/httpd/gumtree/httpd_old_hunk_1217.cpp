                sk_X509_pop_free(cert_stack, X509_free);
            }
        }
        else {
            request_rec *id = r->main ? r->main : r;

            /* do a full renegotiation */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Performing full renegotiation: "
                          "complete handshake protocol");

            SSL_set_session_id_context(ssl,
                                       (unsigned char *)&id,
                                       sizeof(id));

            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Re-negotiation request failed");

                r->connection->aborted = 1;
                return HTTP_FORBIDDEN;
            }

            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
