SSL_CTX * Ssl::generateSslContextUsingPkeyAndCertFromMemory(const char * data)
{
    Ssl::X509_Pointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    if (!readCertAndPrivateKeyFromMemory(cert, pkey, data))
        return NULL;

    if (!cert || !pkey)
        return NULL;

    return createSSLContext(cert, pkey);
}