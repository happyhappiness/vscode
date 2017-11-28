void Ssl::CertificateDb::subSize(std::string const & filename) {
    // readSize will rebuild 'size' file if missing or it is corrupted
    size_t dbSize = readSize();
    const size_t fileSize = getFileSize(filename);
    dbSize = dbSize > fileSize ? dbSize - fileSize : 0;
    writeSize(dbSize);
}