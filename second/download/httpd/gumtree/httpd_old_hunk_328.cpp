         * that the client replies to a Hello Request). But because we insist
         * on a reply (anything else is an error for us) we have to go to the
         * ACCEPT state manually. Using SSL_set_accept_state() doesn't work
         * here because it resets too much of the connection.  So we set the
         * state explicitly and continue the handshake manually.
         */
        ssl_log(r->server, SSL_LOG_INFO,
                "Requesting connection re-negotiation");

        if (renegotiate_quick) {
            STACK_OF(X509) *cert_stack;

            /* perform just a manual re-verification of the peer */
            ssl_log(r->server, SSL_LOG_TRACE,
                    "Performing quick renegotiation: "
                    "just re-verifying the peer");

            cert_stack = (STACK_OF(X509) *)SSL_get_peer_cert_chain(ssl);

            if (!cert_stack || (sk_X509_num(cert_stack) == 0)) {
                ssl_log(r->server, SSL_LOG_ERROR,
                        "Cannot find peer certificate chain");

                return HTTP_FORBIDDEN;
            }

            if (!(cert_store ||
                  (cert_store = SSL_CTX_get_cert_store(ctx))))
            {
                ssl_log(r->server, SSL_LOG_ERROR,
                        "Cannot find certificate storage");

                return HTTP_FORBIDDEN;
            }

            cert = sk_X509_value(cert_stack, 0);
            X509_STORE_CTX_init(&cert_store_ctx, cert_store, cert, cert_stack);
            depth = SSL_get_verify_depth(ssl);

            if (depth >= 0) {
                X509_STORE_CTX_set_depth(&cert_store_ctx, depth);
            }

            X509_STORE_CTX_set_ex_data(&cert_store_ctx,
                                       SSL_get_ex_data_X509_STORE_CTX_idx(),
                                       (char *)ssl);

            if (!modssl_X509_verify_cert(&cert_store_ctx)) {
                ssl_log(r->server, SSL_LOG_ERROR|SSL_ADD_SSLERR, 
                        "Re-negotiation verification step failed");
            }

            SSL_set_verify_result(ssl, cert_store_ctx.error);
            X509_STORE_CTX_cleanup(&cert_store_ctx);
        }
        else {
            request_rec *id = r->main ? r->main : r;

            /* do a full renegotiation */
            ssl_log(r->server, SSL_LOG_TRACE,
                    "Performing full renegotiation: "
                    "complete handshake protocol");

            SSL_set_session_id_context(ssl,
                                       (unsigned char *)&id,
                                       sizeof(id));

            SSL_renegotiate(ssl);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ssl_log(r->server, SSL_LOG_ERROR,
                        "Re-negotiation request failed");

                return HTTP_FORBIDDEN;
            }

            ssl_log(r->server, SSL_LOG_INFO,
                    "Awaiting re-negotiation handshake");

            SSL_set_state(ssl, SSL_ST_ACCEPT);
            SSL_do_handshake(ssl);

            if (SSL_get_state(ssl) != SSL_ST_OK) {
                ssl_log(r->server, SSL_LOG_ERROR,
                        "Re-negotiation handshake failed: "
                        "Not accepted by client!?");

                return HTTP_FORBIDDEN;
            }
        }

