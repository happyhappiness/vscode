ssl_algo_t ssl_util_algotypeof(X509 *pCert, EVP_PKEY *pKey)
{
    ssl_algo_t t;
    EVP_PKEY *pFreeKey = NULL;

    t = SSL_ALGO_UNKNOWN;
    if (pCert != NULL)
        pFreeKey = pKey = X509_get_pubkey(pCert);
    if (pKey != NULL) {
        switch (EVP_PKEY_key_type(pKey)) {
            case EVP_PKEY_RSA:
                t = SSL_ALGO_RSA;
                break;
            case EVP_PKEY_DSA:
                t = SSL_ALGO_DSA;
                break;
            default:
                break;
        }
    }
#ifdef OPENSSL_VERSION_NUMBER
    /* Only refcounted in OpenSSL */
    if (pFreeKey != NULL)
        EVP_PKEY_free(pFreeKey);
#endif
    return t;
}