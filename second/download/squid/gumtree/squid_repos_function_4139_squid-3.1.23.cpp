size_t Ssl::CertificateDb::size() const
{
    FileLocker size_locker(size_full);
    return readSize();
}