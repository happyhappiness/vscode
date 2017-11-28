bool Ssl::appendCertToMemory(Ssl::X509_Pointer const & cert, std::string & bufferToWrite)
{
    if (!cert)
        return false;

    BIO_Pointer bio(BIO_new(BIO_s_mem()));
    if (!bio)
        return false;

    if (!PEM_write_bio_X509 (bio.get(), cert.get()))
        return false;

    char *ptr = NULL;
    long len = BIO_get_mem_data(bio.get(), &ptr);
    if (!ptr)
        return false;

    if (!bufferToWrite.empty())
        bufferToWrite.append(" "); // add a space...

    bufferToWrite.append(ptr, len);
    return true;
}