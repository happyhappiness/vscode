void Ssl::CertificateDb::create(std::string const & db_path) {
    if (db_path == "")
        throw std::runtime_error("Path to db is empty");
    std::string db_full(db_path + "/" + db_file);
    std::string cert_full(db_path + "/" + cert_dir);
    std::string size_full(db_path + "/" + size_file);

    if (mkdir(db_path.c_str(), 0777))
        throw std::runtime_error("Cannot create " + db_path);

    if (mkdir(cert_full.c_str(), 0777))
        throw std::runtime_error("Cannot create " + cert_full);

    std::ofstream size(size_full.c_str());
    if (size)
        size << 0;
    else
        throw std::runtime_error("Cannot open " + size_full + " to open");
    std::ofstream db(db_full.c_str());
    if (!db)
        throw std::runtime_error("Cannot open " + db_full + " to open");
}