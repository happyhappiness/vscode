BOOL SSL_X509_getIDs(apr_pool_t *p, X509 *x509, apr_array_header_t **ids)
{
    STACK_OF(GENERAL_NAME) *names;
    BIO *bio;
    X509_NAME *subj;
    char **cpp;
    int i, n;

    if (!x509 || !(*ids = apr_array_make(p, 0, sizeof(char *)))) {
        *ids = NULL;
        return FALSE;
    }

    /* First, the DNS-IDs (dNSName entries in the subjectAltName extension) */
    if ((names = X509_get_ext_d2i(x509, NID_subject_alt_name, NULL, NULL)) &&
        (bio = BIO_new(BIO_s_mem()))) {
        GENERAL_NAME *name;

        for (i = 0; i < sk_GENERAL_NAME_num(names); i++) {
            name = sk_GENERAL_NAME_value(names, i);
            if (name->type == GEN_DNS) {
                ASN1_STRING_print_ex(bio, name->d.ia5, ASN1_STRFLGS_ESC_CTRL|
                                     ASN1_STRFLGS_UTF8_CONVERT);
                n = BIO_pending(bio);
                if (n > 0) {
                    cpp = (char **)apr_array_push(*ids);
                    *cpp = apr_palloc(p, n+1);
                    n = BIO_read(bio, *cpp, n);
                    (*cpp)[n] = NUL;
                }
            }
        }
        BIO_free(bio);
    }

    if (names)
        sk_GENERAL_NAME_pop_free(names, GENERAL_NAME_free);

    /* Second, the CN-IDs (commonName attributes in the subject DN) */
    subj = X509_get_subject_name(x509);
    i = -1;
    while ((i = X509_NAME_get_index_by_NID(subj, NID_commonName, i)) != -1) {
        cpp = (char **)apr_array_push(*ids);
        *cpp = SSL_X509_NAME_ENTRY_to_string(p, X509_NAME_get_entry(subj, i));
    }

    return apr_is_empty_array(*ids) ? FALSE : TRUE;
}