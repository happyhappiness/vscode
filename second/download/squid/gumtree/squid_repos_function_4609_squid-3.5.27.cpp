size_t Ssl::CertificateDb::readSize() {
    std::ifstream ifstr(size_full.c_str());
    size_t db_size = 0;
    if (!ifstr || !(ifstr >> db_size))
        return rebuildSize();
    return db_size;
}