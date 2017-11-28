size_t Ssl::CertificateDb::readSize() const {
    std::ifstream size_file(size_full.c_str());
    if (!size_file && enabled_disk_store)
        throw std::runtime_error("cannot open for reading: " + size_full);
    size_t db_size = 0;
    if (!(size_file >> db_size))
        throw std::runtime_error("error while reading " + size_full);
    return db_size;
}