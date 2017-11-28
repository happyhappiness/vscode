const char *Ssl::CommonHostName(X509 *x509)
{
    return getSubjectEntry(x509, NID_commonName);
}