void Ssl::CertificateDb::addSize(std::string const & filename)
{
    FileLocker size_locker(size_full);
    writeSize(readSize() + getFileSize(filename));
}