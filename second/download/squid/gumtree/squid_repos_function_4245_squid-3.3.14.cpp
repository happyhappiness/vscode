static bool buildCertificate(Ssl::X509_Pointer & cert, Ssl::CertificateProperties const &properties)
{
    // not an Ssl::X509_NAME_Pointer because X509_REQ_get_subject_name()
    // returns a pointer to the existing subject name. Nothing to clean here.
    if (properties.mimicCert.get()) {
        // Leave subject empty if we cannot extract it from true cert.
        if (X509_NAME *name = X509_get_subject_name(properties.mimicCert.get())) {
            // X509_set_subject_name will call X509_dup for name
            X509_set_subject_name(cert.get(), name);
        }
    }

    if (properties.setCommonName || !properties.mimicCert.get()) {
        // In this case the CN of the certificate given by the user
        // Ignore errors: it is better to make a certificate with no CN
        // than to quit ssl_crtd because we cannot make a certificate.
        // Most errors are caused by user input such as huge domain names.
        (void)replaceCommonName(cert, properties.commonName);
    }

    // We should get caCert notBefore and notAfter fields and do not allow
    // notBefore/notAfter values from certToMimic before/after notBefore/notAfter
    // fields from caCert.
    // Currently there is not any way in openssl tollkit to compare two ASN1_TIME
    // objects.
    ASN1_TIME *aTime = NULL;
    if (!properties.setValidBefore && properties.mimicCert.get())
        aTime = X509_get_notBefore(properties.mimicCert.get());
    if (!aTime && properties.signWithX509.get())
        aTime = X509_get_notBefore(properties.signWithX509.get());

    if (aTime) {
        if (!X509_set_notBefore(cert.get(), aTime))
            return false;
    } else if (!X509_gmtime_adj(X509_get_notBefore(cert.get()), (-2)*24*60*60))
        return false;

    aTime = NULL;
    if (!properties.setValidAfter && properties.mimicCert.get())
        aTime = X509_get_notAfter(properties.mimicCert.get());
    if (!aTime && properties.signWithX509.get())
        aTime = X509_get_notAfter(properties.signWithX509.get());
    if (aTime) {
        if (!X509_set_notAfter(cert.get(), aTime))
            return false;
    } else if (!X509_gmtime_adj(X509_get_notAfter(cert.get()), 60*60*24*356*3))
        return false;

    // mimic the alias and possibly subjectAltName
    if (properties.mimicCert.get()) {
        unsigned char *alStr;
        int alLen;
        alStr = X509_alias_get0(properties.mimicCert.get(), &alLen);
        if (alStr) {
            X509_alias_set1(cert.get(), alStr, alLen);
        }

        // Mimic subjectAltName unless we used a configured CN: browsers reject
        // certificates with CN unrelated to subjectAltNames.
        if (!properties.setCommonName) {
            int pos=X509_get_ext_by_NID (properties.mimicCert.get(), OBJ_sn2nid("subjectAltName"), -1);
            X509_EXTENSION *ext=X509_get_ext(properties.mimicCert.get(), pos);
            if (ext) {
                X509_add_ext(cert.get(), ext, -1);
                /* According the RFC 5280 using extensions requires version 3
                   certificate.
                   Set version value to 2 for version 3 certificates.
                 */
                X509_set_version(cert.get(), 2);
            }
        }

        mimicExtensions(cert, properties.mimicCert);
    }

    return true;
}