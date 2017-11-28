static bool
findCertIssuer(Security::CertList const &list, X509 *cert)
{
    for (Security::CertList::const_iterator it = list.begin(); it != list.end(); ++it) {
        if (X509_check_issued(it->get(), cert) == X509_V_OK)
            return true;
    }
    return false;
}