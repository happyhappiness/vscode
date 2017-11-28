bool Ssl::CertificateDb::addCertAndPrivateKey(Ssl::X509_Pointer & cert, Ssl::EVP_PKEY_Pointer & pkey, std::string const & useName) {
    const Locker locker(dbLock, Here);
    load();
    if (!db || !cert || !pkey)
        return false;
    Row row;
    ASN1_INTEGER * ai = X509_get_serialNumber(cert.get());
    std::string serial_string;
    Ssl::BIGNUM_Pointer serial(ASN1_INTEGER_to_BN(ai, NULL));
    {
        TidyPointer<char, tidyFree> hex_bn(BN_bn2hex(serial.get()));
        serial_string = std::string(hex_bn.get());
    }
    row.setValue(cnlSerial, serial_string.c_str());
    char ** rrow = TXT_DB_get_by_index(db.get(), cnlSerial, row.getRow());
    // We are creating certificates with unique serial numbers. If the serial
    // number is found in the database, the same certificate is already stored.
    if (rrow != NULL) {
        // TODO: check if the stored row is valid.
        return true;
    }

    {
        TidyPointer<char, tidyFree> subject(X509_NAME_oneline(X509_get_subject_name(cert.get()), NULL, 0));
        Ssl::X509_Pointer findCert;
        Ssl::EVP_PKEY_Pointer findPkey;
        if (pure_find(useName.empty() ? subject.get() : useName, findCert, findPkey)) {
            // Replace with database certificate
            cert.reset(findCert.release());
            pkey.reset(findPkey.release());
            return true;
        }
        // pure_find may fail because the entry is expired, or because the
        // certs file is corrupted. Remove any entry with given hostname
        deleteByHostname(useName.empty() ? subject.get() : useName);
    }

    // check db size while trying to minimize calls to size()
    size_t dbSize = size();
    if ((dbSize == 0 && hasRows()) ||
            (dbSize > 0 && !hasRows()) ||
            (dbSize >  10 * max_db_size)) {
        // Invalid database size, rebuild
        dbSize = rebuildSize();
    }
    while (dbSize > max_db_size && deleteInvalidCertificate()) {
        dbSize = size(); // get the current database size
        // and try to find another invalid certificate if needed
    }
    // there are no more invalid ones, but there must be valid certificates
    while (dbSize > max_db_size) {
        if (!deleteOldestCertificate()) {
            rebuildSize(); // No certificates in database.Update the size file.
            save(); // Some entries may have been removed. Update the index file.
            return false; // errors prevented us from freeing enough space
        }
        dbSize = size(); // get the current database size
    }

    row.setValue(cnlType, "V");
    ASN1_UTCTIME * tm = X509_get_notAfter(cert.get());
    row.setValue(cnlExp_date, std::string(reinterpret_cast<char *>(tm->data), tm->length).c_str());
    row.setValue(cnlFile, "unknown");
    if (!useName.empty())
        row.setValue(cnlName, useName.c_str());
    else {
        TidyPointer<char, tidyFree> subject(X509_NAME_oneline(X509_get_subject_name(cert.get()), NULL, 0));
        row.setValue(cnlName, subject.get());
    }

    if (!TXT_DB_insert(db.get(), row.getRow())) {
        // failed to add index (???) but we may have already modified
        // the database so save before exit
        save();
        return false;
    }
    rrow = row.getRow();
    row.reset();

    std::string filename(cert_full + "/" + serial_string + ".pem");
    if (!writeCertAndPrivateKeyToFile(cert, pkey, filename.c_str())) {
        //remove row from txt_db and save
        sq_TXT_DB_delete(db.get(), (const char **)rrow);
        save();
        return false;
    }
    addSize(filename);

    save();
    return true;
}