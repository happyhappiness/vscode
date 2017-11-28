bool Ssl::CertificateDb::deleteByHostname(std::string const & host)
{
    if (!db)
        return false;

#if OPENSSL_VERSION_NUMBER >= 0x1000004fL
    for (int i = 0; i < sk_OPENSSL_PSTRING_num(db.get()->data); i++) {
        const char ** current_row = ((const char **)sk_OPENSSL_PSTRING_value(db.get()->data, i));
#else
    for (int i = 0; i < sk_num(db.get()->data); i++) {
        const char ** current_row = ((const char **)sk_value(db.get()->data, i));
#endif
        if (host == current_row[cnlName]) {
            std::string filename(cert_full + "/" + current_row[cnlSerial] + ".pem");
            FileLocker cert_locker(filename);
#if OPENSSL_VERSION_NUMBER >= 0x1000004fL
            sk_OPENSSL_PSTRING_delete(db.get()->data, i);
#else
            sk_delete(db.get()->data, i);
#endif
            subSize(filename);
            remove(filename.c_str());
            return true;
        }
    }
    return false;
}

bool Ssl::CertificateDb::IsEnabledDiskStore() const
{
    return enabled_disk_store;
}