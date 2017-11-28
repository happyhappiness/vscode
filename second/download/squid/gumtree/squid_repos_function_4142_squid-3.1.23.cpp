size_t Ssl::CertificateDb::readSize() const
{
    size_t db_size;
    std::ifstream size_file(size_full.c_str());
    if (!size_file && enabled_disk_store)
        throw std::runtime_error("cannot read \"" + size_full + "\" file");
    size_file >> db_size;
    return db_size;
}