            sslconn->client_dn = NULL;
        }

        /*
         * Finally check for acceptable renegotiation results
         */
        if ((dc->nVerifyClient != SSL_CVERIFY_NONE) ||
            (sc->server->auth.verify_mode != SSL_CVERIFY_NONE)) {
            BOOL do_verify = ((dc->nVerifyClient == SSL_CVERIFY_REQUIRE) ||
                              (sc->server->auth.verify_mode == SSL_CVERIFY_REQUIRE));

            if (do_verify && (SSL_get_verify_result(ssl) != X509_V_OK)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Re-negotiation handshake failed: "
                              "Client verification failed");

                return HTTP_FORBIDDEN;
            }

            if (do_verify) {
                if ((peercert = SSL_get_peer_certificate(ssl)) == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Re-negotiation handshake failed: "
                                  "Client certificate missing");

                    return HTTP_FORBIDDEN;
                }

                X509_free(peercert);
            }
