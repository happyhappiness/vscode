static char *ssl_var_lookup_ssl_cert_dn(apr_pool_t *p, X509_NAME *xsname, char *var)
{
    char *result, *ptr;
    X509_NAME_ENTRY *xsne;
    int i, j, n, idx = 0;
    apr_size_t varlen;

    /* if an _N suffix is used, find the Nth attribute of given name */
    ptr = strchr(var, '_');
    if (ptr != NULL && strspn(ptr + 1, "0123456789") == strlen(ptr + 1)) {
        idx = atoi(ptr + 1);
        varlen = ptr - var;
    } else {
        varlen = strlen(var);
    }

    result = NULL;

    for (i = 0; ssl_var_lookup_ssl_cert_dn_rec[i].name != NULL; i++) {
        if (strEQn(var, ssl_var_lookup_ssl_cert_dn_rec[i].name, varlen)
            && strlen(ssl_var_lookup_ssl_cert_dn_rec[i].name) == varlen) {
            for (j = 0; j < X509_NAME_entry_count(xsname); j++) {
                xsne = X509_NAME_get_entry(xsname, j);

                n =OBJ_obj2nid((ASN1_OBJECT *)X509_NAME_ENTRY_get_object(xsne));

                if (n == ssl_var_lookup_ssl_cert_dn_rec[i].nid && idx-- == 0) {
                    result = modssl_X509_NAME_ENTRY_to_string(p, xsne);
                    break;
                }
            }
            break;
        }
    }
    return result;
}