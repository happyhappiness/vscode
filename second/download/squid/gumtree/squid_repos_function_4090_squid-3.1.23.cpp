static EVP_PKEY * readSslPrivateKey(char const * keyFilename)
{
    if (!keyFilename)
        return NULL;
    Ssl::BIO_Pointer bio(BIO_new(BIO_s_file_internal()));
    if (!bio)
        return NULL;
    if (!BIO_read_filename(bio.get(), keyFilename))
        return NULL;
    EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio.get(), NULL, NULL, NULL);
    return pkey;
}