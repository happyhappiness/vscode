static int
mimicExtensions(Ssl::X509_Pointer & cert, Ssl::X509_Pointer const & mimicCert)
{
    static int extensions[]= {
        NID_key_usage,
        NID_ext_key_usage,
        NID_basic_constraints,
        0
    };

    // key usage bit names
    enum {
        DigitalSignature,
        NonRepudiation,
        KeyEncipherment, // NSS requires for RSA but not EC
        DataEncipherment,
        KeyAgreement,
        KeyCertificateSign,
        CRLSign,
        EncipherOnly,
        DecipherOnly
    };

    int mimicAlgo = OBJ_obj2nid(mimicCert.get()->cert_info->key->algor->algorithm);

    int added = 0;
    int nid;
    for (int i = 0; (nid = extensions[i]) != 0; ++i) {
        const int pos = X509_get_ext_by_NID(mimicCert.get(), nid, -1);
        if (X509_EXTENSION *ext = X509_get_ext(mimicCert.get(), pos)) {
            // Mimic extension exactly.
            if (X509_add_ext(cert.get(), ext, -1))
                ++added;
            if ( nid == NID_key_usage && mimicAlgo != NID_rsaEncryption ) {
                // NSS does not requre the KeyEncipherment flag on EC keys
                // but it does require it for RSA keys.  Since ssl-bump
                // substitutes RSA keys for EC ones, we need to ensure that
                // that the more stringent requirements are met.

                const int p = X509_get_ext_by_NID(cert.get(), NID_key_usage, -1);
                if ((ext = X509_get_ext(cert.get(), p)) != NULL) {
                    ASN1_BIT_STRING *keyusage = (ASN1_BIT_STRING *)X509V3_EXT_d2i(ext);
                    ASN1_BIT_STRING_set_bit(keyusage, KeyEncipherment, 1);

                    //Build the ASN1_OCTET_STRING
                    const X509V3_EXT_METHOD *method = X509V3_EXT_get(ext);
                    assert(method && method->it);
                    unsigned char *ext_der = NULL;
                    int ext_len = ASN1_item_i2d((ASN1_VALUE *)keyusage,
                                                &ext_der,
                                                (const ASN1_ITEM *)ASN1_ITEM_ptr(method->it));

                    ASN1_OCTET_STRING *ext_oct = M_ASN1_OCTET_STRING_new();
                    ext_oct->data = ext_der;
                    ext_oct->length = ext_len;
                    X509_EXTENSION_set_data(ext, ext_oct);

                    M_ASN1_OCTET_STRING_free(ext_oct);
                    ASN1_BIT_STRING_free(keyusage);
                }
            }
        }
    }

    // We could also restrict mimicking of the CA extension to CA:FALSE
    // because Squid does not generate valid fake CA certificates.

    return added;
}