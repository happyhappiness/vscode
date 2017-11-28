const char *
Ssl::GetX509Fingerprint(X509 * cert, const char *)
{
    static char buf[1024];
    if (!cert)
        return NULL;

    unsigned int n;
    unsigned char md[EVP_MAX_MD_SIZE];
    if (!X509_digest(cert, EVP_sha1(), md, &n))
        return NULL;

    assert(3 * n + 1 < sizeof(buf));

    char *s = buf;
    for (unsigned int i=0; i < n; ++i, s += 3) {
        const char term = (i + 1 < n) ? ':' : '\0';
        snprintf(s, 4, "%02X%c", md[i], term);
    }

    return buf;
}