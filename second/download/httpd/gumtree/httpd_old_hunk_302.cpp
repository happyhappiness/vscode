    EVP_PKEY *pkey;

    if (!(asn1 = ssl_asn1_table_get(mc->tPrivateKey, id))) {
        return FALSE;
    }

    ssl_log(s, SSL_LOG_TRACE|SSL_INIT,
            "Configuring %s server private key", type);

    ptr = asn1->cpData;
    if (!(pkey = d2i_PrivateKey(pkey_type, NULL, &ptr, asn1->nData)))
    {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_INIT,
                "Unable to import %s server private key", type);
        ssl_die();
    }

    if (SSL_CTX_use_PrivateKey(mctx->ssl_ctx, pkey) <= 0) {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_INIT,
                "Unable to configure %s server private key", type);
        ssl_die();
    }

    /*
     * XXX: wonder if this is still needed, this is old todo doc.
     * (see http://www.psy.uq.edu.au/~ftp/Crypto/ssleay/TODO.html)
     */
    if ((pkey_type == EVP_PKEY_DSA) && mctx->pks->certs[idx]) {
        EVP_PKEY *pubkey = X509_get_pubkey(mctx->pks->certs[idx]);

        if (pubkey && EVP_PKEY_missing_parameters(pubkey)) {
            EVP_PKEY_copy_parameters(pubkey, pkey);
            ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_INIT,
                    "Copying DSA parameters from private key to certificate");
        }
    }

    mctx->pks->keys[idx] = pkey;

    return TRUE;
