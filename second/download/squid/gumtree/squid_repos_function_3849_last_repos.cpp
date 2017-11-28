Security::ContextPointer
Ssl::generateSslContext(CertificateProperties const &properties, AnyP::PortCfg &port)
{
    Security::CertPointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    if (!generateSslCertificate(cert, pkey, properties) || !cert || !pkey)
        return Security::ContextPointer();

    return createSSLContext(cert, pkey, port);
}