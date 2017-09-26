        idx = SSL_TMP_KEY_DH_1024;
    }

    return (DH *)mc->pTmpKeys[idx];
}

/*
 * This OpenSSL callback function is called when OpenSSL
 * does client authentication and verifies the certificate chain.
 */
int ssl_callback_SSLVerify(int ok, X509_STORE_CTX *ctx)
{
