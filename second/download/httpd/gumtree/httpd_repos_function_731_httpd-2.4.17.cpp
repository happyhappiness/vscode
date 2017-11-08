char *modssl_X509_NAME_ENTRY_to_string(apr_pool_t *p, X509_NAME_ENTRY *xsne)
{
    char *result = asn1_string_to_utf8(p, X509_NAME_ENTRY_get_data(xsne));
    ap_xlate_proto_from_ascii(result, len);
    return result;
}