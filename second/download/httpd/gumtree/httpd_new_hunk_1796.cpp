{
    const char *keystr = ssl_asn1_keystr(keytype);

    return apr_pstrcat(p, id, ":", keystr, NULL);
}

STACK_OF(X509) *ssl_read_pkcs7(server_rec *s, const char *pkcs7)
{
    PKCS7 *p7;
    STACK_OF(X509) *certs = NULL;
    FILE *f;

    f = fopen(pkcs7, "r");
    if (!f) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "Can't open %s", pkcs7);
        ssl_die();
    }

    p7 = PEM_read_PKCS7(f, NULL, NULL, NULL);
    if (!p7) {
        ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
                     "Can't read PKCS7 object %s", pkcs7);
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_CRIT, s);
        exit(1);
    }

    switch (OBJ_obj2nid(p7->type)) {
    case NID_pkcs7_signed:
        certs = p7->d.sign->cert;
        p7->d.sign->cert = NULL;
        PKCS7_free(p7);
        break;

    case NID_pkcs7_signedAndEnveloped:
        certs = p7->d.signed_and_enveloped->cert;
        p7->d.signed_and_enveloped->cert = NULL;
        PKCS7_free(p7);
        break;

    default:
        ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_NOERRNO, 0, s,
                     "Don't understand PKCS7 file %s", pkcs7);
        ssl_die();
    }

    if (!certs) {
        ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_NOERRNO, 0, s,
                     "No certificates in %s", pkcs7);
        ssl_die();
    }

    fclose(f);

    return certs;
}


#if APR_HAS_THREADS
/*
 * To ensure thread-safetyness in OpenSSL - work in progress
 */

