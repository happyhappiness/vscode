bool Ssl::verifySslCertificate(SSL_CTX * sslContext, CertificateProperties const &properties)
{
    // SSL_get_certificate is buggy in openssl versions 1.0.1d and 1.0.1e
    // Try to retrieve certificate directly from SSL_CTX object
#if SQUID_USE_SSLGETCERTIFICATE_HACK
    X509 ***pCert = (X509 ***)sslContext->cert;
    X509 * cert = pCert && *pCert ? **pCert : NULL;
#elif SQUID_SSLGETCERTIFICATE_BUGGY
    X509 * cert = NULL;
    assert(0);
#else
    // Temporary ssl for getting X509 certificate from SSL_CTX.
    Ssl::SSL_Pointer ssl(SSL_new(sslContext));
    X509 * cert = SSL_get_certificate(ssl.get());
#endif
    if (!cert)
        return false;
    ASN1_TIME * time_notBefore = X509_get_notBefore(cert);
    ASN1_TIME * time_notAfter = X509_get_notAfter(cert);
    bool ret = (X509_cmp_current_time(time_notBefore) < 0 && X509_cmp_current_time(time_notAfter) > 0);
    if (!ret)
        return false;

    return certificateMatchesProperties(cert, properties);
}