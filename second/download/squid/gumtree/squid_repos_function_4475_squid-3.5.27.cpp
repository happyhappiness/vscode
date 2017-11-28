bool
Ssl::configureSSL(SSL *ssl, CertificateProperties const &properties, AnyP::PortCfg &port)
{
    Ssl::X509_Pointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    if (!generateSslCertificate(cert, pkey, properties))
        return false;

    if (!cert)
        return false;

    if (!pkey)
        return false;

    if (!SSL_use_certificate(ssl, cert.get()))
        return false;

    if (!SSL_use_PrivateKey(ssl, pkey.get()))
        return false;

    return true;
}