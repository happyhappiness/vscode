SSL_CTX * Ssl::generateSslContext(char const *host, Ssl::X509_Pointer const & signedX509, Ssl::EVP_PKEY_Pointer const & signedPkey)
{
    Ssl::X509_Pointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    if (!generateSslCertificateAndPrivateKey(host, signedX509, signedPkey, cert, pkey, NULL)) {
        return NULL;
    }
    if (!cert)
        return NULL;

    if (!pkey)
        return NULL;

    return createSSLContext(cert, pkey);
}