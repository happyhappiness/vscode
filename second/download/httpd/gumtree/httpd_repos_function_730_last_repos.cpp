BOOL modssl_X509_getSAN(apr_pool_t *p, X509 *x509, int type, const char *onf,
                        int idx, apr_array_header_t **entries)
{
    STACK_OF(GENERAL_NAME) *names;
    int nid = onf ? OBJ_txt2nid(onf) : NID_undef;

    if (!x509 || (type < GEN_OTHERNAME) ||
        ((type == GEN_OTHERNAME) && (nid == NID_undef)) ||
        (type > GEN_RID) || (idx < -1) ||
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

            if (name->type != type)
                continue;

            switch (type) {
            case GEN_EMAIL:
            case GEN_DNS:
                if (((idx == -1) || (n == idx)) &&
                    (utf8str = asn1_string_to_utf8(p, name->d.ia5))) {
                    APR_ARRAY_PUSH(*entries, const char *) = utf8str;
                }
                n++;
                break;
            case GEN_OTHERNAME:
                if (OBJ_obj2nid(name->d.otherName->type_id) == nid) {
                    if (((idx == -1) || (n == idx))) {
                        parse_otherName_value(p, name->d.otherName->value,
                                              onf, entries);
                    }
                    n++;
                }
                break;
            default:
                /*
                 * Not implemented right now:
                 * GEN_X400 (x400Address)
                 * GEN_DIRNAME (directoryName)
                 * GEN_EDIPARTY (ediPartyName)
                 * GEN_URI (uniformResourceIdentifier)
                 * GEN_IPADD (iPAddress)
                 * GEN_RID (registeredID)
                 */
                break;
            }

            if ((idx != -1) && (n > idx))
               break;
        }

        sk_GENERAL_NAME_pop_free(names, GENERAL_NAME_free);
    }

    return apr_is_empty_array(*entries) ? FALSE : TRUE;
}