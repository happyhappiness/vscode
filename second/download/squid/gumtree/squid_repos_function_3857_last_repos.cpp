bool
Ssl::loadCerts(const char *certsFile, Ssl::CertsIndexedList &list)
{
    BIO *in = BIO_new_file(certsFile, "r");
    if (!in) {
        debugs(83, DBG_IMPORTANT, "Failed to open '" << certsFile << "' to load certificates");
        return false;
    }

    X509 *aCert;
    while((aCert = PEM_read_bio_X509(in, NULL, NULL, NULL))) {
        static char buffer[2048];
        X509_NAME_oneline(X509_get_subject_name(aCert), buffer, sizeof(buffer));
        list.insert(std::pair<SBuf, X509 *>(SBuf(buffer), aCert));
    }
    debugs(83, 4, "Loaded " << list.size() << " certificates from file: '" << certsFile << "'");
    BIO_free(in);
    return true;
}