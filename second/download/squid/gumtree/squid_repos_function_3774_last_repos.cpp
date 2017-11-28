static bool replaceCommonName(Security::CertPointer & cert, std::string const &rawCn)
{
    std::string cn = rawCn;

    if (cn.length() > MaxCnLen) {
        // In the case the length od CN is more than the maximum supported size
        // try to use the first upper level domain.
        size_t pos = 0;
        do {
            pos = cn.find('.', pos + 1);
        } while (pos != std::string::npos && (cn.length() - pos + 2) > MaxCnLen);

        // If no short domain found or this domain is a toplevel domain
        // we failed to find a good cn name.
        if (pos == std::string::npos || cn.find('.', pos + 1) == std::string::npos)
            return false;

        std::string fixedCn(1, '*');
        fixedCn.append(cn.c_str() + pos);
        cn = fixedCn;
    }

    // Assume [] surround an IPv6 address and strip them because browsers such
    // as Firefox, Chromium, and Safari prefer bare IPv6 addresses in CNs.
    if (cn.length() > 2 && *cn.begin() == '[' && *cn.rbegin() == ']')
        cn = cn.substr(1, cn.size()-2);

    X509_NAME *name = X509_get_subject_name(cert.get());
    if (!name)
        return false;
    // Remove the CN part:
    int loc = X509_NAME_get_index_by_NID(name, NID_commonName, -1);
    if (loc >=0) {
        X509_NAME_ENTRY *tmp = X509_NAME_get_entry(name, loc);
        X509_NAME_delete_entry(name, loc);
        X509_NAME_ENTRY_free(tmp);
    }

    // Add a new CN
    return X509_NAME_add_entry_by_NID(name, NID_commonName, MBSTRING_ASC,
                                      (unsigned char *)(cn.c_str()), -1, -1, 0);
}