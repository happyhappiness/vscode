std::string Ssl::CertificateDb::getSNString() const
{
    FileLocker serial_locker(serial_full);
    std::ifstream file(serial_full.c_str());
    if (!file)
        return "";
    std::string serial;
    file >> serial;
    return serial;
}