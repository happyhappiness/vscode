        /*
         * Check date of CRL to make sure it's not expired
         */
        i = X509_cmp_current_time(X509_CRL_get_nextUpdate(crl));

        if (i == 0) {
            ssl_log(s, SSL_LOG_WARN,
                    "Found CRL has invalid nextUpdate field");

            X509_STORE_CTX_set_error(ctx,
                                     X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD);
            X509_OBJECT_free_contents(&obj);

            return FALSE;
        }

        if (i < 0) {
            ssl_log(s, SSL_LOG_WARN,
                    "Found CRL is expired - "
                    "revoking all certificates until you get updated CRL");

            X509_STORE_CTX_set_error(ctx, X509_V_ERR_CRL_HAS_EXPIRED);
            X509_OBJECT_free_contents(&obj);

            return FALSE;
        }
