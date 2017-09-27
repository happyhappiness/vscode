
        /* Verify authentication of the whole salt+IV+ciphertext by computing
         * the MAC and comparing it (timing safe) with the one in the payload.
         */
        compute_auth(slider, len, passphrase, passlen, auth);
        if (!ap_crypto_equals(auth, decoded, AP_SIPHASH_DSIZE)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO()
                    "auth does not match, skipping");
            continue;
        }

        /* encrypt using the first passphrase in the list */
        res = apr_crypto_passphrase(&key, &ivSize, passphrase, passlen,
