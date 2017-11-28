Security::ContextPointer
Ssl::generateSslContextUsingPkeyAndCertFromMemory(const char * data, AnyP::PortCfg &port)
{
    Security::CertPointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    if (!readCertAndPrivateKeyFromMemory(cert, pkey, data) || !cert || !pkey)
        return Security::ContextPointer();

    return createSSLContext(cert, pkey, port);
}