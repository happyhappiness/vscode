bool Ssl::CertificateDb::deleteOldestCertificate()
{
    if (!db)
        return false;

#if OPENSSL_VERSION_NUMBER >= 0x1000004fL
    if (sk_OPENSSL_PSTRING_num(db.get()->data) == 0)
#else
    if (sk_num(db.get()->data) == 0)
#endif
        return false;

#if OPENSSL_VERSION_NUMBER >= 0x1000004fL
    const char **row = (const char **)sk_OPENSSL_PSTRING_value(db.get()->data, 0);
#else
    const char **row = (const char **)sk_value(db.get()->data, 0);
#endif
    std::string filename(cert_full + "/" + row[cnlSerial] + ".pem");
    FileLocker cert_locker(filename);

#if OPENSSL_VERSION_NUMBER >= 0x1000004fL
    sk_OPENSSL_PSTRING_delete(db.get()->data, 0);
#else
    sk_delete(db.get()->data, 0);
#endif

    subSize(filename);
    remove(filename.c_str());

    return true;
}