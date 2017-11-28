int Ssl::matchX509CommonNames(X509 *peer_cert, void *check_data, int (*check_func)(void *check_data,  ASN1_STRING *cn_data))
{
    assert(peer_cert);

    X509_NAME *name = X509_get_subject_name(peer_cert);

    for (int i = X509_NAME_get_index_by_NID(name, NID_commonName, -1); i >= 0; i = X509_NAME_get_index_by_NID(name, NID_commonName, i)) {

        ASN1_STRING *cn_data = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(name, i));

        if ( (*check_func)(check_data, cn_data) == 0)
            return 1;
    }

    STACK_OF(GENERAL_NAME) * altnames;
    altnames = (STACK_OF(GENERAL_NAME)*)X509_get_ext_d2i(peer_cert, NID_subject_alt_name, NULL, NULL);

    if (altnames) {
        int numalts = sk_GENERAL_NAME_num(altnames);
        for (int i = 0; i < numalts; i++) {
            const GENERAL_NAME *check = sk_GENERAL_NAME_value(altnames, i);
            if (check->type != GEN_DNS) {
                continue;
            }
            ASN1_STRING *cn_data = check->d.dNSName;

            if ( (*check_func)(check_data, cn_data) == 0) {
                sk_GENERAL_NAME_pop_free(altnames, GENERAL_NAME_free);
                return 1;
            }
        }
        sk_GENERAL_NAME_pop_free(altnames, GENERAL_NAME_free);
    }
    return 0;
}