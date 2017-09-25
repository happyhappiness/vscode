            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, buff);
        }

        /*
         * Verify the signature on this CRL
         */
        if (X509_CRL_verify(crl, X509_get_pubkey(cert)) <= 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "Invalid signature on CRL");

            X509_STORE_CTX_set_error(ctx, X509_V_ERR_CRL_SIGNATURE_FAILURE);
            X509_OBJECT_free_contents(&obj);

            return FALSE;
        }

        /*
         * Check date of CRL to make sure it's not expired
         */
        i = X509_cmp_current_time(X509_CRL_get_nextUpdate(crl));

        if (i == 0) {
