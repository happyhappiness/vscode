        EVP_PKEY *pubkey = X509_get_pubkey(mctx->pks->certs[idx]);

        if (pubkey && EVP_PKEY_missing_parameters(pubkey)) {
            EVP_PKEY_copy_parameters(pubkey, pkey);
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Copying DSA parameters from private key to certificate");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            EVP_PKEY_free(pubkey);
        }
    }

    mctx->pks->keys[idx] = pkey;

