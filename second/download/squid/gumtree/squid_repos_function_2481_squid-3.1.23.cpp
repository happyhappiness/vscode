static SSL_CTX * createSSLContext(Ssl::X509_Pointer & x509, Ssl::EVP_PKEY_Pointer & pkey)
{
    Ssl::SSL_CTX_Pointer sslContext(SSL_CTX_new(SSLv23_server_method()));

    if (!SSL_CTX_use_certificate(sslContext.get(), x509.get()))
        return NULL;

    if (!SSL_CTX_use_PrivateKey(sslContext.get(), pkey.get()))
        return NULL;
    return sslContext.release();
}