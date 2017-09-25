            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, buff);
        }

        /*
         * Verify the signature on this CRL
         */
        pubkey = X509_get_pubkey(cert);
        if (X509_CRL_verify(crl, pubkey) <= 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                         "Invalid signature on CRL");

            X509_STORE_CTX_set_error(ctx, X509_V_ERR_CRL_SIGNATURE_FAILURE);
            X509_OBJECT_free_contents(&obj);
            if (pubkey)
                EVP_PKEY_free(pubkey);

            return FALSE;
        }

        if (pubkey)
            EVP_PKEY_free(pubkey);

        /*
         * Check date of CRL to make sure it's not expired
         */
        i = X509_cmp_current_time(X509_CRL_get_nextUpdate(crl));

        if (i == 0) {
