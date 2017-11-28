void Ssl::CertificateDb::writeSize(size_t db_size) {
    std::ofstream size_file(size_full.c_str());
    if (!size_file && enabled_disk_store)
        throw std::runtime_error("cannot write \"" + size_full + "\" file");
    size_file << db_size;
}