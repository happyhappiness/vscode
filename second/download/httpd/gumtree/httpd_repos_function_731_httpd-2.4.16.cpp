BOOL SSL_X509_getSAN(apr_pool_t *p, X509 *x509, int type, int idx,
                     apr_array_header_t **entries)
{
    STACK_OF(GENERAL_NAME) *names;

    if (!x509 || (type < GEN_OTHERNAME) || (type > GEN_RID) || (idx < -1) ||
        !(*entries = apr_array_make(p, 0, sizeof(char *)))) {
        *entries = NULL;
        return FALSE;
    }

    if ((names = X509_get_ext_d2i(x509, NID_subject_alt_name, NULL, NULL))) {
        int i, n = 0;
        GENERAL_NAME *name;
        const char *utf8str;

        for (i = 0; i < sk_GENERAL_NAME_num(names); i++) {
            name = sk_GENERAL_NAME_value(names, i);
            if (name->type == type) {
                if ((idx == -1) || (n == idx)) {
                    switch (type) {
                    case GEN_EMAIL:
                    case GEN_DNS:
                        utf8str = SSL_ASN1_STRING_to_utf8(p, name->d.ia5);
                        if (utf8str) {
                            APR_ARRAY_PUSH(*entries, const char *) = utf8str;
                        }
                        break;
                    default:
                        /*
                         * Not implemented right now:
                         * GEN_OTHERNAME (otherName)
                         * GEN_X400 (x400Address)
                         * GEN_DIRNAME (directoryName)
                         * GEN_EDIPARTY (ediPartyName)
                         * GEN_URI (uniformResourceIdentifier)
                         * GEN_IPADD (iPAddress)
                         * GEN_RID (registeredID)
                         */
                        break;
                    }
                }
                if ((idx != -1) && (n++ > idx))
                   break;
            }
        }

        sk_GENERAL_NAME_pop_free(names, GENERAL_NAME_free);
    }

    return apr_is_empty_array(*entries) ? FALSE : TRUE;
}