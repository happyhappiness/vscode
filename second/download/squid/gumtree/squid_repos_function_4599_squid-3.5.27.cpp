bool Ssl::CertificateDb::find(std::string const & host_name, Ssl::X509_Pointer & cert, Ssl::EVP_PKEY_Pointer & pkey) {
    const Locker locker(dbLock, Here);
    load();
    return pure_find(host_name, cert, pkey);
}