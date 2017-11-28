bool Ssl::writeCertAndPrivateKeyToFile(Security::CertPointer const & cert, Ssl::EVP_PKEY_Pointer const & pkey, char const * filename)
{
    if (!pkey || !cert)
        return false;

    Ssl::BIO_Pointer bio(BIO_new(BIO_s_file()));
    if (!bio)
        return false;
    if (!BIO_write_filename(bio.get(), const_cast<char *>(filename)))
        return false;

    if (!PEM_write_bio_X509(bio.get(), cert.get()))
        return false;

    if (!PEM_write_bio_PrivateKey(bio.get(), pkey.get(), NULL, NULL, 0, NULL, NULL))
        return false;

    return true;
}