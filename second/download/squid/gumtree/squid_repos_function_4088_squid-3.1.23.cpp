bool Ssl::generateSslCertificateAndPrivateKey(char const *host, Ssl::X509_Pointer const & signedX509, Ssl::EVP_PKEY_Pointer const & signedPkey, Ssl::X509_Pointer & cert, Ssl::EVP_PKEY_Pointer & pkey, BIGNUM const * serial)
{
    pkey.reset(createSslPrivateKey());
    if (!pkey)
        return false;

    Ssl::X509_REQ_Pointer request(createNewX509Request(pkey, host));
    if (!request)
        return false;

    if (signedX509.get() && signedPkey.get())
        cert.reset(signRequest(request, signedX509, signedPkey, X509_get_notAfter(signedX509.get()), serial));
    else
        cert.reset(signRequest(request, signedX509, pkey, NULL, serial));

    if (!cert)
        return false;

    return true;
}