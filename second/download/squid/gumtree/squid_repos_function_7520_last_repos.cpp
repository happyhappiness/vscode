size_t Ssl::CertificateDb::rebuildSize()
{
    size_t dbSize = 0;
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
        const std::string filename(cert_full + "/" + current_row[cnlSerial] + ".pem");
        const size_t fSize = getFileSize(filename);
        dbSize += fSize;
    }
    writeSize(dbSize);
    return dbSize;
}

bool Ssl::CertificateDb::pure_find(std::string const & host_name, Security::CertPointer & cert, Ssl::EVP_PKEY_Pointer & pkey) {
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

size_t Ssl::CertificateDb::size() {
    return readSize();
}

void Ssl::CertificateDb::addSize(std::string const & filename) {
    // readSize will rebuild 'size' file if missing or it is corrupted
    size_t dbSize = readSize();
    dbSize += getFileSize(filename);
    writeSize(dbSize);
}

void Ssl::CertificateDb::subSize(std::string const & filename) {
    // readSize will rebuild 'size' file if missing or it is corrupted
    size_t dbSize = readSize();
    const size_t fileSize = getFileSize(filename);
    dbSize = dbSize > fileSize ? dbSize - fileSize : 0;
    writeSize(dbSize);
}

size_t Ssl::CertificateDb::readSize() {
    std::ifstream ifstr(size_full.c_str());
    size_t db_size = 0;
    if (!ifstr || !(ifstr >> db_size))
        return rebuildSize();
    return db_size;
}

void Ssl::CertificateDb::writeSize(size_t db_size) {
    std::ofstream ofstr(size_full.c_str());
    if (!ofstr)
        throw std::runtime_error("cannot write \"" + size_full + "\" file");
    ofstr << db_size;
}

size_t Ssl::CertificateDb::getFileSize(std::string const & filename) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file)
        return 0;
    file.seekg(0, std::ios_base::end);
    const std::streampos file_size = file.tellg();
    if (file_size < 0)
        return 0;
    return ((static_cast<size_t>(file_size) + fs_block_size - 1) / fs_block_size) * fs_block_size;
}

void Ssl::CertificateDb::load() {
    // Load db from file.
    Ssl::BIO_Pointer in(BIO_new(BIO_s_file()));
    if (!in || BIO_read_filename(in.get(), db_full.c_str()) <= 0)
        throw std::runtime_error("Uninitialized SSL certificate database directory: " + db_path + ". To initialize, run \"security_file_certgen -c -s " + db_path + "\".");

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

void Ssl::CertificateDb::save() {
    if (!db)
        throw std::runtime_error("The certificates database is not loaded");;

    // To save the db to file,  create a new BIO with BIO file methods.
    Ssl::BIO_Pointer out(BIO_new(BIO_s_file()));
    if (!out || !BIO_write_filename(out.get(), const_cast<char *>(db_full.c_str())))
        throw std::runtime_error("Failed to initialize " + db_full + " file for writing");;

    if (TXT_DB_write(out.get(), db.get()) < 0)
        throw std::runtime_error("Failed to write " + db_full + " file");
}

// Normally defined in defines.h file
void Ssl::CertificateDb::deleteRow(const char **row, int rowIndex) {
    const std::string filename(cert_full + "/" + row[cnlSerial] + ".pem");
    sq_TXT_DB_delete_row(db.get(), rowIndex);

    subSize(filename);
    int ret = remove(filename.c_str());
    if (ret < 0 && errno != ENOENT)
        throw std::runtime_error("Failed to remove certficate file " + filename + " from db");
}

bool Ssl::CertificateDb::deleteInvalidCertificate() {
    if (!db)
        return false;

    bool removed_one = false;
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

        if (!sslDateIsInTheFuture(current_row[cnlExp_date])) {
            deleteRow(current_row, i);
            removed_one = true;
            break;
        }
    }

    if (!removed_one)
        return false;
    return true;
}

bool Ssl::CertificateDb::deleteOldestCertificate()
{
    if (!hasRows())
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