bool Ssl::CertificateDb::find(std::string const & host_name, Security::CertPointer & cert, Ssl::EVP_PKEY_Pointer & pkey) {
    const Locker locker(dbLock, Here);
    load();
    return pure_find(host_name, cert, pkey);
}