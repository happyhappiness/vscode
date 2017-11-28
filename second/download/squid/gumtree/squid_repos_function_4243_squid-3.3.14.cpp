std::string & Ssl::CertificateProperties::dbKey() const
{
    static std::string certKey;
    certKey.clear();
    certKey.reserve(4096);
    if (mimicCert.get()) {
        char buf[1024];
        certKey.append(X509_NAME_oneline(X509_get_subject_name(mimicCert.get()), buf, sizeof(buf)));
    }

    if (certKey.empty()) {
        certKey.append("/CN=", 4);
        certKey.append(commonName);
    }

    if (setValidAfter)
        certKey.append("+SetValidAfter=on", 17);

    if (setValidBefore)
        certKey.append("+SetValidBefore=on", 18);

    if (setCommonName) {
        certKey.append("+SetCommonName=", 15);
        certKey.append(commonName);
    }

    if (signAlgorithm != Ssl::algSignEnd) {
        certKey.append("+Sign=", 6);
        certKey.append(certSignAlgorithm(signAlgorithm));
    }

    return certKey;
}