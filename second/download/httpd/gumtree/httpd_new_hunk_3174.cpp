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
