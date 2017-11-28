const char *Ssl::getOrganization(X509 *x509)
{
    return getSubjectEntry(x509, NID_organizationName);
}