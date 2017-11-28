void Ssl::CertificateDb::addSize(std::string const & filename) {
    writeSize(readSize() + getFileSize(filename));
}