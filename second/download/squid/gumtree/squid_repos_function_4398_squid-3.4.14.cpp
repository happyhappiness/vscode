void Ssl::CertificateDb::sq_TXT_DB_delete_row(TXT_DB *db, int idx) {
    char **rrow;
#if SQUID_SSLTXTDB_PSTRINGDATA
    rrow = (char **)sk_OPENSSL_PSTRING_delete(db->data, idx);
#else
    rrow = (char **)sk_delete(db->data, idx);
#endif

    if (!rrow)
        return;

    Row row(rrow, cnlNumber); // row wrapper used to free the rrow

    const Columns db_indexes[]={cnlSerial, cnlName};
    for (unsigned int i = 0; i < countof(db_indexes); ++i) {
        void *data = NULL;
#if SQUID_SSLTXTDB_PSTRINGDATA
        if (LHASH_OF(OPENSSL_STRING) *fieldIndex =  db->index[db_indexes[i]])
            data = lh_OPENSSL_STRING_delete(fieldIndex, rrow);
#else
        if (LHASH *fieldIndex = db->index[db_indexes[i]])
            data = lh_delete(fieldIndex, rrow);
#endif
        if (data)
            assert(data == rrow);
    }
}