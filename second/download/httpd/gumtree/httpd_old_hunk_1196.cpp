                 */
                cert_stack = sk_new_null();
                sk_X509_push(cert_stack, MODSSL_PCHAR_CAST cert);
            }

            if (!cert_stack || (sk_X509_num(cert_stack) == 0)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Cannot find peer certificate chain");

                return HTTP_FORBIDDEN;
            }

            if (!(cert_store ||
                  (cert_store = SSL_CTX_get_cert_store(ctx))))
            {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "Cannot find certificate storage");

                return HTTP_FORBIDDEN;
            }

            if (!cert) {
                cert = sk_X509_value(cert_stack, 0);
