X509 * Ssl::signRequest(Ssl::X509_REQ_Pointer const & request, Ssl::X509_Pointer const & x509, Ssl::EVP_PKEY_Pointer const & pkey, ASN1_TIME * timeNotAfter, BIGNUM const * serial)
{
    Ssl::X509_Pointer cert(X509_new());
    if (!cert)
        return NULL;

    if (!setSerialNumber(X509_get_serialNumber(cert.get()), serial))
        return NULL;

    if (!X509_set_issuer_name(cert.get(), x509.get() ? X509_get_subject_name(x509.get()) : X509_REQ_get_subject_name(request.get())))
        return NULL;

    if (!X509_gmtime_adj(X509_get_notBefore(cert.get()), (-2)*24*60*60))
        return NULL;

    if (timeNotAfter) {
        if (!X509_set_notAfter(cert.get(), timeNotAfter))
            return NULL;
    } else if (!X509_gmtime_adj(X509_get_notAfter(cert.get()), 60*60*24*356*3))
        return NULL;

    if (!X509_set_subject_name(cert.get(), X509_REQ_get_subject_name(request.get())))
        return NULL;

    Ssl::EVP_PKEY_Pointer tmppkey(X509_REQ_get_pubkey(request.get()));

    if (!tmppkey || !X509_set_pubkey(cert.get(), tmppkey.get()))
        return NULL;

    if (!X509_sign(cert.get(), pkey.get(), EVP_sha1()))
        return NULL;

    return cert.release();
}