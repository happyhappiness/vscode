bool Ssl::writeCertAndPrivateKeyToMemory(Ssl::X509_Pointer const & cert, Ssl::EVP_PKEY_Pointer const & pkey, std::string & bufferToWrite)
{
    bufferToWrite.clear();
    if (!pkey || !cert)
        return false;
    BIO_Pointer bio(BIO_new(BIO_s_mem()));
    if (!bio)
        return false;

    if (!PEM_write_bio_X509 (bio.get(), cert.get()))
        return false;

    if (!PEM_write_bio_PrivateKey(bio.get(), pkey.get(), NULL, NULL, 0, NULL, NULL))
        return false;

    char *ptr = NULL;
    long len = BIO_get_mem_data(bio.get(), &ptr);
    if (!ptr)
        return false;

    bufferToWrite = std::string(ptr, len);
    return true;
}