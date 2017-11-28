unsigned long Ssl::CertificateDb::index_name_hash(const char **a)
{
    return(lh_strhash(a[Ssl::CertificateDb::cnlName]));
}