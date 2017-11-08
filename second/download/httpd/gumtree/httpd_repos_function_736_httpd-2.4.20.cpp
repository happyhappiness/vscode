static BOOL getIDs(apr_pool_t *p, X509 *x509, apr_array_header_t **ids)
{
    X509_NAME *subj;
    int i = -1;

    /* First, the DNS-IDs (dNSName entries in the subjectAltName extension) */
    if (!x509 ||
        (modssl_X509_getSAN(p, x509, GEN_DNS, NULL, -1, ids) == FALSE && !*ids)) {
        *ids = NULL;
        return FALSE;
    }

    /* Second, the CN-IDs (commonName attributes in the subject DN) */
    subj = X509_get_subject_name(x509);
    while ((i = X509_NAME_get_index_by_NID(subj, NID_commonName, i)) != -1) {
        APR_ARRAY_PUSH(*ids, const char *) = 
            modssl_X509_NAME_ENTRY_to_string(p, X509_NAME_get_entry(subj, i));
    }

    return apr_is_empty_array(*ids) ? FALSE : TRUE;
}