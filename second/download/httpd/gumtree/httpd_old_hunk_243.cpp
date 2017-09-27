
            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Re-negotiation handshake failed: "
                        "Not accepted by client!?");

                return HTTP_FORBIDDEN;
            }
        }

        /*
         * Remember the peer certificate's DN
         */
        if ((cert = SSL_get_peer_certificate(ssl))) {
            sslconn->client_cert = cert;
            sslconn->client_dn = NULL;
            X509_free(cert);
        }

        /*
         * Finally check for acceptable renegotiation results
         */
        if (dc->nVerifyClient != SSL_CVERIFY_NONE) {
