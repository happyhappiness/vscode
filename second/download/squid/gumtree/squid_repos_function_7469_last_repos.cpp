void
Security::PeerOptions::loadCrlFile()
{
    parsedCrl.clear();
    if (crlFile.isEmpty())
        return;

#if USE_OPENSSL
    BIO *in = BIO_new_file(crlFile.c_str(), "r");
    if (!in) {
        debugs(83, 2, "WARNING: Failed to open CRL file " << crlFile);
        return;
    }

    while (X509_CRL *crl = PEM_read_bio_X509_CRL(in,NULL,NULL,NULL)) {
        parsedCrl.emplace_back(Security::CrlPointer(crl));
    }
    BIO_free(in);
#endif
}