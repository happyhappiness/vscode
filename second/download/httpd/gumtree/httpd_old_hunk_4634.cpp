            }

            if (!cert) {
                cert = sk_X509_value(cert_stack, 0);
            }

            X509_STORE_CTX_init(&cert_store_ctx, cert_store, cert, cert_stack);
            depth = SSL_get_verify_depth(ssl);

            if (depth >= 0) {
                X509_STORE_CTX_set_depth(&cert_store_ctx, depth);
            }

            X509_STORE_CTX_set_ex_data(&cert_store_ctx,
                                       SSL_get_ex_data_X509_STORE_CTX_idx(),
                                       (char *)ssl);

            if (!X509_verify_cert(&cert_store_ctx)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02224)
                              "Re-negotiation verification step failed");
                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);
            }

            SSL_set_verify_result(ssl, cert_store_ctx.error);
            X509_STORE_CTX_cleanup(&cert_store_ctx);

            if (cert_stack != SSL_get_peer_cert_chain(ssl)) {
                /* we created this ourselves, so free it */
                sk_X509_pop_free(cert_stack, X509_free);
            }
        }
        else {
            const char *reneg_support;
            request_rec *id = r->main ? r->main : r;

            /* Additional mitigation for CVE-2009-3555: At this point,
             * before renegotiating, an (entire) request has been read
             * from the connection.  An attacker may have sent further
