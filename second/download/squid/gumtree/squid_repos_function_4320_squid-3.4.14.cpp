static SSL_CTX *
createSSLContext(Ssl::X509_Pointer & x509, Ssl::EVP_PKEY_Pointer & pkey, AnyP::PortCfg &port)
{
    Ssl::SSL_CTX_Pointer sslContext(SSL_CTX_new(port.contextMethod));

    if (!SSL_CTX_use_certificate(sslContext.get(), x509.get()))
        return NULL;

    if (!SSL_CTX_use_PrivateKey(sslContext.get(), pkey.get()))
        return NULL;

    if (!configureSslContext(sslContext.get(), port))
        return NULL;

    return sslContext.release();
}