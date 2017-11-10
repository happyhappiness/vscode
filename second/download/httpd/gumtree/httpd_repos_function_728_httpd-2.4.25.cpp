static void parse_otherName_value(apr_pool_t *p, ASN1_TYPE *value,
                                  const char *onf, apr_array_header_t **entries)
{
    const char *str;
    int nid = onf ? OBJ_txt2nid(onf) : NID_undef;

    if (!value || (nid == NID_undef) || !*entries)
       return;

    /* 
     * Currently supported otherName forms (values for "onf"):
     * "msUPN" (1.3.6.1.4.1.311.20.2.3): Microsoft User Principal Name
     * "id-on-dnsSRV" (1.3.6.1.5.5.7.8.7): SRVName, as specified in RFC 4985
     */
    if ((nid == NID_ms_upn) && (value->type == V_ASN1_UTF8STRING) &&
        (str = asn1_string_to_utf8(p, value->value.utf8string))) {
        APR_ARRAY_PUSH(*entries, const char *) = str;
    } else if (strEQ(onf, "id-on-dnsSRV") &&
               (value->type == V_ASN1_IA5STRING) &&
               (str = asn1_string_to_utf8(p, value->value.ia5string))) {
        APR_ARRAY_PUSH(*entries, const char *) = str;
    }
}