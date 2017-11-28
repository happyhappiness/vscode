unsigned long Ssl::CertificateDb::index_serial_hash(const char **a) {
    const char *n = a[Ssl::CertificateDb::cnlSerial];
    while (*n == '0')
        ++n;
    return lh_strhash(n);
}