char *SSL_X509_NAME_ENTRY_to_string(apr_pool_t *p, X509_NAME_ENTRY *xsne)
{
    char *result = SSL_ASN1_STRING_to_utf8(p, X509_NAME_ENTRY_get_data(xsne));
    ap_xlate_proto_from_ascii(result, len);
    return result;
}