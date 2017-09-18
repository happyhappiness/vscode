         * Finally check for acceptable renegotiation results
         */
        if (dc->nVerifyClient != SSL_CVERIFY_NONE) {
            BOOL do_verify = (dc->nVerifyClient == SSL_CVERIFY_REQUIRE);

            if (do_verify && (SSL_get_verify_result(ssl) != X509_V_OK)) {
                ssl_log(r->server, SSL_LOG_ERROR,
                        "Re-negotiation handshake failed: "
                        "Client verification failed");

                return HTTP_FORBIDDEN;
            }

            if (do_verify && !SSL_get_peer_certificate(ssl)) {
                ssl_log(r->server, SSL_LOG_ERROR,
                        "Re-negotiation handshake failed: "
                        "Client certificate missing");

                return HTTP_FORBIDDEN;
            }
        }
    }

