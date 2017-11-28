void Ssl::CertificateDb::addSize(std::string const & filename) {
    // readSize will rebuild 'size' file if missing or it is corrupted
    size_t dbSize = readSize();
    dbSize += getFileSize(filename);
    writeSize(dbSize);
}