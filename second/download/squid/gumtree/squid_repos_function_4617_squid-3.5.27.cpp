bool Ssl::CertificateDb::deleteByHostname(std::string const & host) {
    if (!db)
        return false;

#if SQUID_SSLTXTDB_PSTRINGDATA
    for (int i = 0; i < sk_OPENSSL_PSTRING_num(db.get()->data); ++i) {
#if SQUID_STACKOF_PSTRINGDATA_HACK
        const char ** current_row = ((const char **)sk_value(CHECKED_STACK_OF(OPENSSL_PSTRING, db.get()->data), i));
#else
        const char ** current_row = ((const char **)sk_OPENSSL_PSTRING_value(db.get()->data, i));
#endif
#else
    for (int i = 0; i < sk_num(db.get()->data); ++i) {
        const char ** current_row = ((const char **)sk_value(db.get()->data, i));
#endif
        if (host == current_row[cnlName]) {
            deleteRow(current_row, i);
            return true;
        }
    }
    return false;
}

bool Ssl::CertificateDb::hasRows() const
{
    if (!db)
        return false;

#if SQUID_SSLTXTDB_PSTRINGDATA
    if (sk_OPENSSL_PSTRING_num(db.get()->data) == 0)
#else
    if (sk_num(db.get()->data) == 0)
#endif
        return false;
    return true;
}

bool Ssl::CertificateDb::IsEnabledDiskStore() const {
    return enabled_disk_store;
}