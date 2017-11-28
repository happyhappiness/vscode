void Ssl::readCertAndPrivateKeyFromFiles(Ssl::X509_Pointer & cert, Ssl::EVP_PKEY_Pointer & pkey, char const * certFilename, char const * keyFilename)
{
    if (keyFilename == NULL)
        keyFilename = certFilename;
    pkey.reset(readSslPrivateKey(keyFilename));
    cert.reset(readSslX509Certificate(certFilename));
    if (!pkey || !cert || !X509_check_private_key(cert.get(), pkey.get())) {
        pkey.reset(NULL);
        cert.reset(NULL);
    }
}