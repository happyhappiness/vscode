bool Ssl::CertificateDb::pure_find(std::string const & host_name, Ssl::X509_Pointer & cert, Ssl::EVP_PKEY_Pointer & pkey) {
    if (!db)
        return false;

    Row row;
    row.setValue(cnlName, host_name.c_str());

    char **rrow = TXT_DB_get_by_index(db.get(), cnlName, row.getRow());
    if (rrow == NULL)
        return false;

    if (!sslDateIsInTheFuture(rrow[cnlExp_date]))
        return false;

    // read cert and pkey from file.
    std::string filename(cert_full + "/" + rrow[cnlSerial] + ".pem");
    readCertAndPrivateKeyFromFiles(cert, pkey, filename.c_str(), NULL);
    if (!cert || !pkey)
        return false;
    return true;
}