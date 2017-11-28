void
Security::HandshakeParser::ParseCertificate(const SBuf &raw, Security::CertPointer &pCert)
{
#if USE_OPENSSL
    auto x509Start = reinterpret_cast<const unsigned char *>(raw.rawContent());
    auto x509Pos = x509Start;
    X509 *x509 = d2i_X509(nullptr, &x509Pos, raw.length());
    pCert.resetWithoutLocking(x509);
    Must(x509); // successfully parsed
    Must(x509Pos == x509Start + raw.length()); // no leftovers
#else
    // workaround GCC -O3 error with unused variables. see bug 4663.
    (void)pCert;
    debugs(83, 2, "TLS parsing is not supported without OpenSSL. " << raw);
#endif
}