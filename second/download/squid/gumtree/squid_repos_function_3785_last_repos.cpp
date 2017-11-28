bool Ssl::generateSslCertificate(Security::CertPointer & certToStore, Ssl::EVP_PKEY_Pointer & pkeyToStore, Ssl::CertificateProperties const &properties)
{
    Ssl::BIGNUM_Pointer serial;

    if (!createSerial(serial, properties))
        return false;

    return  generateFakeSslCertificate(certToStore, pkeyToStore, properties, serial);
}