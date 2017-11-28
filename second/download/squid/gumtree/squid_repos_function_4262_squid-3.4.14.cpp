bool Ssl::readCertFromMemory(X509_Pointer & cert, char const * bufferToRead)
{
    Ssl::BIO_Pointer bio(BIO_new(BIO_s_mem()));
    BIO_puts(bio.get(), bufferToRead);

    X509 * certPtr = NULL;
    cert.reset(PEM_read_bio_X509(bio.get(), &certPtr, 0, 0));
    if (!cert)
        return false;

    return true;
}