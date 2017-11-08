static char *ssl_var_lookup_ssl_cert_dn(apr_pool_t *p, X509_NAME *xsname, char *var)
{
    char *result;
    X509_NAME_ENTRY *xsne;
    int i, j, n;
    unsigned char *data_ptr;
    int data_len;

    result = NULL;

    for (i = 0; ssl_var_lookup_ssl_cert_dn_rec[i].name != NULL; i++) {
        if (strEQ(var, ssl_var_lookup_ssl_cert_dn_rec[i].name)) {
            for (j = 0; j < sk_X509_NAME_ENTRY_num((STACK_OF(X509_NAME_ENTRY) *)
                                                 X509_NAME_get_entries(xsname));
                 j++) {
                xsne = sk_X509_NAME_ENTRY_value((STACK_OF(X509_NAME_ENTRY) *)
                                             X509_NAME_get_entries(xsname), j);

                n =OBJ_obj2nid((ASN1_OBJECT *)X509_NAME_ENTRY_get_object(xsne));
                data_ptr = X509_NAME_ENTRY_get_data_ptr(xsne);
                data_len = X509_NAME_ENTRY_get_data_len(xsne);

                if (n == ssl_var_lookup_ssl_cert_dn_rec[i].nid) {
                    result = apr_palloc(p, data_len+1);
                    apr_cpystrn(result, (char *)data_ptr, data_len+1);
#ifdef CHARSET_EBCDIC
                    ascii2ebcdic(result, result, xsne->value->length);
#endif /* CHARSET_EBCDIC */
                    result[data_len] = NUL;
                    break;
                }
            }
            break;
        }
    }
    return result;
}