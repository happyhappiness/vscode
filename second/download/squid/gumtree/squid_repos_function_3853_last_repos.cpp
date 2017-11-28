bool
Ssl::configureSSLUsingPkeyAndCertFromMemory(SSL *ssl, const char *data, AnyP::PortCfg &port)
{
    Security::CertPointer cert;
    Ssl::EVP_PKEY_Pointer pkey;
    if (!readCertAndPrivateKeyFromMemory(cert, pkey, data))
        return false;

    if (!cert || !pkey)
        return false;

    if (!SSL_use_certificate(ssl, cert.get()))
        return false;

    if (!SSL_use_PrivateKey(ssl, pkey.get()))
        return false;

    return true;
}