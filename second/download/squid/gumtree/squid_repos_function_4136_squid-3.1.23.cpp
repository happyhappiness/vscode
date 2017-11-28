void Ssl::CertificateDb::check(std::string const & db_path, size_t max_db_size)
{
    CertificateDb db(db_path, max_db_size, 0);
}