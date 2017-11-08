BOOL SSL_X509_getCN(apr_pool_t *p, X509 *xs, char **cppCN)
{
    X509_NAME *xsn;
    X509_NAME_ENTRY *xsne;
    int i, nid;
    unsigned char *data_ptr;
    int data_len;

    xsn = X509_get_subject_name(xs);
    for (i = 0; i < sk_X509_NAME_ENTRY_num((STACK_OF(X509_NAME_ENTRY) *)
                                           X509_NAME_get_entries(xsn)); i++) {
        xsne = sk_X509_NAME_ENTRY_value((STACK_OF(X509_NAME_ENTRY) *)
                                         X509_NAME_get_entries(xsn), i);
        nid = OBJ_obj2nid((ASN1_OBJECT *)X509_NAME_ENTRY_get_object(xsne));
        if (nid == NID_commonName) {
            data_ptr = X509_NAME_ENTRY_get_data_ptr(xsne);
            data_len = X509_NAME_ENTRY_get_data_len(xsne);
            *cppCN = apr_palloc(p, data_len+1);
            apr_cpystrn(*cppCN, (char *)data_ptr, data_len+1);
            (*cppCN)[data_len] = NUL;
#ifdef CHARSET_EBCDIC
            ascii2ebcdic(*cppCN, *cppCN, strlen(*cppCN));
#endif
            return TRUE;
        }
    }
    return FALSE;
}