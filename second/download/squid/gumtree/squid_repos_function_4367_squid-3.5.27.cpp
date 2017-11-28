bool Ssl::readCertAndPrivateKeyFromMemory(Ssl::X509_Pointer & cert, Ssl::EVP_PKEY_Pointer & pkey, char const * bufferToRead)
{
    Ssl::BIO_Pointer bio(BIO_new(BIO_s_mem()));
    BIO_puts(bio.get(), bufferToRead);

    X509 * certPtr = NULL;
    cert.reset(PEM_read_bio_X509(bio.get(), &certPtr, 0, 0));
    if (!cert)
        return false;

    EVP_PKEY * pkeyPtr = NULL;
    pkey.reset(PEM_read_bio_PrivateKey(bio.get(), &pkeyPtr, 0, 0));
    if (!pkey)
        return false;

    return true;
}