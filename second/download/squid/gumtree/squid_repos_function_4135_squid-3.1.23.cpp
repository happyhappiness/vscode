void Ssl::CertificateDb::create(std::string const & db_path, int serial)
{
    if (db_path == "")
        throw std::runtime_error("Path to db is empty");
    std::string serial_full(db_path + "/" + serial_file);
    std::string db_full(db_path + "/" + db_file);
    std::string cert_full(db_path + "/" + cert_dir);
    std::string size_full(db_path + "/" + size_file);

#ifdef _SQUID_MSWIN_
    if (mkdir(db_path.c_str()))
#else
    if (mkdir(db_path.c_str(), 0777))
#endif
        throw std::runtime_error("Cannot create " + db_path);

#ifdef _SQUID_MSWIN_
    if (mkdir(cert_full.c_str()))
#else
    if (mkdir(cert_full.c_str(), 0777))
#endif
        throw std::runtime_error("Cannot create " + cert_full);

    Ssl::ASN1_INT_Pointer i(ASN1_INTEGER_new());
    ASN1_INTEGER_set(i.get(), serial);

    Ssl::BIO_Pointer file(BIO_new(BIO_s_file()));
    if (!file)
        throw std::runtime_error("SSL error");

    if (BIO_write_filename(file.get(), const_cast<char *>(serial_full.c_str())) <= 0)
        throw std::runtime_error("Cannot open " + cert_full + " to open");

    i2a_ASN1_INTEGER(file.get(), i.get());

    std::ofstream size(size_full.c_str());
    if (size)
        size << 0;
    else
        throw std::runtime_error("Cannot open " + size_full + " to open");
    std::ofstream db(db_full.c_str());
    if (!db)
        throw std::runtime_error("Cannot open " + db_full + " to open");
}