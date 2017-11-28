SSL_CTX *
Ssl::generateSslContext(CertificateProperties const &properties, AnyP::PortCfg &port)
{
    Ssl::X509_Pointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    if (!generateSslCertificate(cert, pkey, properties))
        return NULL;

    if (!cert)
        return NULL;

    if (!pkey)
        return NULL;

    return createSSLContext(cert, pkey, port);
}