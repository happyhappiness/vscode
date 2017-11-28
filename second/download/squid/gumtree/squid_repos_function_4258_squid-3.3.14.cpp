bool Ssl::certificateMatchesProperties(X509 *cert, CertificateProperties const &properties)
{
    assert(cert);

    // For non self-signed certificates we have to check if the signing certificate changed
    if (properties.signAlgorithm != Ssl::algSignSelf) {
        assert(properties.signWithX509.get());
        if (X509_check_issued(properties.signWithX509.get(), cert) != X509_V_OK)
            return false;
    }

    X509 *cert2 = properties.mimicCert.get();
    // If there is not certificate to mimic stop here
    if (!cert2)
        return true;

    if (!properties.setCommonName) {
        X509_NAME *cert1_name = X509_get_subject_name(cert);
        X509_NAME *cert2_name = X509_get_subject_name(cert2);
        if (X509_NAME_cmp(cert1_name, cert2_name) != 0)
            return false;
    } else if (properties.commonName != CommonHostName(cert))
        return false;

    if (!properties.setValidBefore) {
        ASN1_TIME *aTime = X509_get_notBefore(cert);
        ASN1_TIME *bTime = X509_get_notBefore(cert2);
        if (asn1time_cmp(aTime, bTime) != 0)
            return false;
    } else if (X509_cmp_current_time(X509_get_notBefore(cert)) >= 0) {
        // notBefore does not exist (=0) or it is in the future (>0)
        return false;
    }

    if (!properties.setValidAfter) {
        ASN1_TIME *aTime = X509_get_notAfter(cert);
        ASN1_TIME *bTime = X509_get_notAfter(cert2);
        if (asn1time_cmp(aTime, bTime) != 0)
            return false;
    } else if (X509_cmp_current_time(X509_get_notAfter(cert)) <= 0) {
        // notAfter does not exist (0) or  it is in the past (<0)
        return false;
    }

    char *alStr1;
    int alLen;
    alStr1 = (char *)X509_alias_get0(cert, &alLen);
    char *alStr2  = (char *)X509_alias_get0(cert2, &alLen);
    if ((!alStr1 && alStr2) || (alStr1 && !alStr2) ||
            (alStr1 && alStr2 && strcmp(alStr1, alStr2)) != 0)
        return false;

    // Compare subjectAltName extension
    STACK_OF(GENERAL_NAME) * cert1_altnames;
    cert1_altnames = (STACK_OF(GENERAL_NAME)*)X509_get_ext_d2i(cert, NID_subject_alt_name, NULL, NULL);
    STACK_OF(GENERAL_NAME) * cert2_altnames;
    cert2_altnames = (STACK_OF(GENERAL_NAME)*)X509_get_ext_d2i(cert2, NID_subject_alt_name, NULL, NULL);
    bool match = true;
    if (cert1_altnames) {
        int numalts = sk_GENERAL_NAME_num(cert1_altnames);
        for (int i = 0; match && i < numalts; ++i) {
            const GENERAL_NAME *aName = sk_GENERAL_NAME_value(cert1_altnames, i);
            match = sk_GENERAL_NAME_find(cert2_altnames, aName);
        }
    } else if (cert2_altnames)
        match = false;

    sk_GENERAL_NAME_pop_free(cert1_altnames, GENERAL_NAME_free);
    sk_GENERAL_NAME_pop_free(cert2_altnames, GENERAL_NAME_free);

    return match;
}