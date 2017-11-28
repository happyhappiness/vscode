void Ssl::CertificateDb::writeSize(size_t db_size) {
    std::ofstream ofstr(size_full.c_str());
    if (!ofstr)
        throw std::runtime_error("cannot write \"" + size_full + "\" file");
    ofstr << db_size;
}