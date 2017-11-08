char *SSL_X509_NAME_ENTRY_to_string(apr_pool_t *p, X509_NAME_ENTRY *xsne)
{
    char *result = NULL;
    BIO* bio;
    int len;

    if ((bio = BIO_new(BIO_s_mem())) == NULL)
        return NULL;
    ASN1_STRING_print_ex(bio, X509_NAME_ENTRY_get_data(xsne),
                         ASN1_STRFLGS_ESC_CTRL|ASN1_STRFLGS_UTF8_CONVERT);
    len = BIO_pending(bio);
    result = apr_palloc(p, len+1);
    len = BIO_read(bio, result, len);
    result[len] = NUL;
    BIO_free(bio);
    ap_xlate_proto_from_ascii(result, len);
    return result;
}