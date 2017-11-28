static bool generateFakeSslCertificate(Ssl::X509_Pointer & certToStore, Ssl::EVP_PKEY_Pointer & pkeyToStore, Ssl::CertificateProperties const &properties,  Ssl::BIGNUM_Pointer const &serial)
{
    Ssl::EVP_PKEY_Pointer pkey;
    // Use signing certificates private key as generated certificate private key
    if (properties.signWithPkey.get())
        pkey.resetAndLock(properties.signWithPkey.get());
    else // if not exist generate one
        pkey.reset(Ssl::createSslPrivateKey());

    if (!pkey)
        return false;

    Ssl::X509_Pointer cert(X509_new());
    if (!cert)
        return false;

    // Set pub key and serial given by the caller
    if (!X509_set_pubkey(cert.get(), pkey.get()))
        return false;
    if (!setSerialNumber(X509_get_serialNumber(cert.get()), serial.get()))
        return false;

    // Fill the certificate with the required properties
    if (!buildCertificate(cert, properties))
        return false;

    int ret = 0;
    // Set issuer name, from CA or our subject name for self signed cert
    if (properties.signAlgorithm != Ssl::algSignSelf && properties.signWithX509.get())
        ret = X509_set_issuer_name(cert.get(), X509_get_subject_name(properties.signWithX509.get()));
    else // Self signed certificate, set issuer to self
        ret = X509_set_issuer_name(cert.get(), X509_get_subject_name(cert.get()));
    if (!ret)
        return false;

    const  EVP_MD *hash = properties.signHash ? properties.signHash : EVP_get_digestbyname(SQUID_SSL_SIGN_HASH_IF_NONE);
    assert(hash);
    /*Now sign the request */
    if (properties.signAlgorithm != Ssl::algSignSelf && properties.signWithPkey.get())
        ret = X509_sign(cert.get(), properties.signWithPkey.get(), hash);
    else //else sign with self key (self signed request)
        ret = X509_sign(cert.get(), pkey.get(), hash);

    if (!ret)
        return false;

    certToStore.reset(cert.release());
    pkeyToStore.reset(pkey.release());
    return true;
}