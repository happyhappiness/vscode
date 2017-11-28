int Ssl::CertificateDb::index_name_cmp(const char **a, const char **b) {
    return(strcmp(a[Ssl::CertificateDb::cnlName], b[CertificateDb::cnlName]));
}