    EVP_PKEY *pkey;

#ifndef OPENSSL_NO_EC
    if (idx == SSL_AIDX_ECC)
      pkey_type = EVP_PKEY_EC;
    else
#endif /* SSL_LIBRARY_VERSION */
    pkey_type = (idx == SSL_AIDX_RSA) ? EVP_PKEY_RSA : EVP_PKEY_DSA;

    if (!(asn1 = ssl_asn1_table_get(mc->tPrivateKey, id))) {
        return FALSE;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring %s server private key", type);

    ptr = asn1->cpData;
    if (!(pkey = d2i_PrivateKey(pkey_type, NULL, &ptr, asn1->nData)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Unable to import %s server private key", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
        ssl_die();
    }

    if (SSL_CTX_use_PrivateKey(mctx->ssl_ctx, pkey) <= 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Unable to configure %s server private key", type);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
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
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "Copying DSA parameters from private key to certificate");
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
            EVP_PKEY_free(pubkey);
        }
    }

