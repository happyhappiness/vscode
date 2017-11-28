void Ssl::CertificateDb::subSize(std::string const & filename) {
    writeSize(readSize() - getFileSize(filename));
}