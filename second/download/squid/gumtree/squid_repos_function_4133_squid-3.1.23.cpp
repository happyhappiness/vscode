bool Ssl::CertificateDb::addCertAndPrivateKey(Ssl::X509_Pointer & cert, Ssl::EVP_PKEY_Pointer & pkey)
{
    FileLocker db_locker(db_full);
    load();
    if (!db || !cert || !pkey || min_db_size > max_db_size)
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
    if (rrow != NULL)
        return false;

    {
        TidyPointer<char, tidyFree> subject(X509_NAME_oneline(X509_get_subject_name(cert.get()), NULL, 0));
        if (pure_find(subject.get(), cert, pkey))
            return true;
    }
    // check db size.
    while (max_db_size < size()) {
        if (!deleteInvalidCertificate())
            break;
    }

    while (max_db_size < size()) {
        deleteOldestCertificate();
    }

    row.setValue(cnlType, "V");
    ASN1_UTCTIME * tm = X509_get_notAfter(cert.get());
    row.setValue(cnlExp_date, std::string(reinterpret_cast<char *>(tm->data), tm->length).c_str());
    row.setValue(cnlFile, "unknown");
    {
        TidyPointer<char, tidyFree> subject(X509_NAME_oneline(X509_get_subject_name(cert.get()), NULL, 0));
        row.setValue(cnlName, subject.get());
    }

    if (!TXT_DB_insert(db.get(), row.getRow()))
        return false;

    row.reset();
    std::string filename(cert_full + "/" + serial_string + ".pem");
    FileLocker cert_locker(filename);
    if (!writeCertAndPrivateKeyToFile(cert, pkey, filename.c_str()))
        return false;
    addSize(filename);

    save();
    return true;
}