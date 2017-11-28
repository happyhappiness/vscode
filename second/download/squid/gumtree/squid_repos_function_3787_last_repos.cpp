EVP_PKEY * Ssl::readSslPrivateKey(char const * keyFilename, pem_password_cb *passwd_callback)
{
    if (!keyFilename)
        return NULL;
    Ssl::BIO_Pointer bio(BIO_new(BIO_s_file()));
    if (!bio)
        return NULL;
    if (!BIO_read_filename(bio.get(), keyFilename))
        return NULL;
    EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio.get(), NULL, passwd_callback, NULL);
    return pkey;
}