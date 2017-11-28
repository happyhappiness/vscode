bool Ssl::CertificateDb::purgeCert(std::string const & key) {
    const Locker locker(dbLock, Here);
    load();
    if (!db)
        return false;

    if (!deleteByHostname(key))
        return false;

    save();
    return true;
}