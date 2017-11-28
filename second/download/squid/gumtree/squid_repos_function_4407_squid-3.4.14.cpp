void Ssl::CertificateDb::check(std::string const & db_path, size_t max_db_size, size_t fs_block_size) {
    CertificateDb db(db_path, max_db_size, fs_block_size);
    db.load();

    // Call readSize to force rebuild size file in the case it is corrupted
    (void)db.readSize();
}