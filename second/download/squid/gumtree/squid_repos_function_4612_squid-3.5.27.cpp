void Ssl::CertificateDb::load() {
    // Load db from file.
    Ssl::BIO_Pointer in(BIO_new(BIO_s_file()));
    if (!in || BIO_read_filename(in.get(), db_full.c_str()) <= 0)
        throw std::runtime_error("Uninitialized SSL certificate database directory: " + db_path + ". To initialize, run \"ssl_crtd -c -s " + db_path + "\".");

    bool corrupt = false;
    Ssl::TXT_DB_Pointer temp_db(TXT_DB_read(in.get(), cnlNumber));
    if (!temp_db)
        corrupt = true;

    // Create indexes in db.
    if (!corrupt && !TXT_DB_create_index(temp_db.get(), cnlSerial, NULL, LHASH_HASH_FN(index_serial_hash), LHASH_COMP_FN(index_serial_cmp)))
        corrupt = true;

    if (!corrupt && !TXT_DB_create_index(temp_db.get(), cnlName, NULL, LHASH_HASH_FN(index_name_hash), LHASH_COMP_FN(index_name_cmp)))
        corrupt = true;

    if (corrupt)
        throw std::runtime_error("The SSL certificate database " + db_path + " is corrupted. Please rebuild");

    db.reset(temp_db.release());
}