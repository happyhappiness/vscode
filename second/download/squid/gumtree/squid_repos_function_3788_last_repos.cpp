void Ssl::readCertAndPrivateKeyFromFiles(Security::CertPointer & cert, Ssl::EVP_PKEY_Pointer & pkey, char const * certFilename, char const * keyFilename)
{
    if (keyFilename == NULL)
        keyFilename = certFilename;
    pkey.resetWithoutLocking(readSslPrivateKey(keyFilename));
    cert.resetWithoutLocking(readSslX509Certificate(certFilename));
    if (!pkey || !cert || !X509_check_private_key(cert.get(), pkey.get())) {
        pkey.reset();
        cert.reset();
    }
}