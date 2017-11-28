int Ssl::CertificateDb::index_serial_cmp(const char **a, const char **b) {
    const char *aa, *bb;
    for (aa = a[Ssl::CertificateDb::cnlSerial]; *aa == '0'; ++aa);
    for (bb = b[Ssl::CertificateDb::cnlSerial]; *bb == '0'; ++bb);
    return strcmp(aa, bb);
}