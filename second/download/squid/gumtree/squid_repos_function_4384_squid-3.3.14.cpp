bool Ssl::CertificateDb::deleteOldestCertificate() {
    if (!db)
        return false;

#if SQUID_SSLTXTDB_PSTRINGDATA
    if (sk_OPENSSL_PSTRING_num(db.get()->data) == 0)
#else
    if (sk_num(db.get()->data) == 0)
#endif
        return false;

#if SQUID_SSLTXTDB_PSTRINGDATA
#if SQUID_STACKOF_PSTRINGDATA_HACK
    const char **row = ((const char **)sk_value(CHECKED_STACK_OF(OPENSSL_PSTRING, db.get()->data), 0));
#else
    const char **row = (const char **)sk_OPENSSL_PSTRING_value(db.get()->data, 0);
#endif
#else
    const char **row = (const char **)sk_value(db.get()->data, 0);
#endif

    deleteRow(row, 0);

    return true;
}