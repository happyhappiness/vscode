static bool
mimicAuthorityKeyId(Security::CertPointer &cert, Security::CertPointer const &mimicCert, Security::CertPointer const &issuerCert)
{
    if (!mimicCert.get() || !issuerCert.get())
        return false;

    Ssl::AUTHORITY_KEYID_Pointer akid((AUTHORITY_KEYID *)X509_get_ext_d2i(mimicCert.get(), NID_authority_key_identifier, nullptr, nullptr));

    bool addKeyId = false, addIssuer = false;
    if (akid.get()) {
        addKeyId = (akid.get()->keyid != nullptr);
        addIssuer = (akid.get()->issuer && akid.get()->serial);
    }

    if (!addKeyId && !addIssuer)
        return false; // No need to add AuthorityKeyIdentifier

    Ssl::ASN1_OCTET_STRING_Pointer issuerKeyId;
    if (addKeyId) {
        X509_EXTENSION *ext;
        // Check if the issuer has the Subject Key Identifier extension
        const int indx = X509_get_ext_by_NID(issuerCert.get(), NID_subject_key_identifier, -1);
        if (indx >= 0 && (ext = X509_get_ext(issuerCert.get(), indx))) {
            issuerKeyId.reset((ASN1_OCTET_STRING *)X509V3_EXT_d2i(ext));
        }
    }

    Ssl::X509_NAME_Pointer issuerName;
    Ssl::ASN1_INT_Pointer issuerSerial;
    if (issuerKeyId.get() == nullptr || addIssuer) {
        issuerName.reset(X509_NAME_dup(X509_get_issuer_name(issuerCert.get())));
        issuerSerial.reset(ASN1_INTEGER_dup(X509_get_serialNumber(issuerCert.get())));
    }

    Ssl::AUTHORITY_KEYID_Pointer theAuthKeyId(AUTHORITY_KEYID_new());
    if (!theAuthKeyId.get())
        return false;
    theAuthKeyId.get()->keyid = issuerKeyId.release();
    if (issuerName && issuerSerial) {
        Ssl::GENERAL_NAME_STACK_Pointer genNames(sk_GENERAL_NAME_new_null());
        if (genNames.get()) {
            if (GENERAL_NAME *aname = GENERAL_NAME_new()) {
                sk_GENERAL_NAME_push(genNames.get(), aname);
                aname->type = GEN_DIRNAME;
                aname->d.dirn = issuerName.release();
                theAuthKeyId.get()->issuer = genNames.release();
                theAuthKeyId.get()->serial = issuerSerial.release();
            }
        }
    }

    // The Authority Key Identifier extension should include KeyId or/and both
    /// issuer name and issuer serial
    if (!theAuthKeyId.get()->keyid && (!theAuthKeyId.get()->issuer || !theAuthKeyId.get()->serial))
        return false;

    const X509V3_EXT_METHOD *method = X509V3_EXT_get_nid(NID_authority_key_identifier);
    if (!method)
        return false;

    unsigned char *ext_der = NULL;
    int ext_len = ASN1_item_i2d((ASN1_VALUE *)theAuthKeyId.get(), &ext_der, ASN1_ITEM_ptr(method->it));
    Ssl::ASN1_OCTET_STRING_Pointer extOct(ASN1_OCTET_STRING_new());
    extOct.get()->data = ext_der;
    extOct.get()->length = ext_len;
    Ssl::X509_EXTENSION_Pointer extAuthKeyId(X509_EXTENSION_create_by_NID(NULL, NID_authority_key_identifier, 0, extOct.get()));
    if (!extAuthKeyId.get())
        return false;

    extOct.release();
    if (!X509_add_ext(cert.get(), extAuthKeyId.get(), -1))
        return false;

    return true;
}