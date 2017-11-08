static int dump_extn_value(BIO *bio, ASN1_OCTET_STRING *str)
{
    MODSSL_D2I_ASN1_type_bytes_CONST unsigned char *pp = str->data;
    ASN1_STRING *ret = ASN1_STRING_new();
    int rv = 0;
    
    /* This allows UTF8String, IA5String, VisibleString, or BMPString;
     * conversion to UTF-8 is forced. */
    if (d2i_DISPLAYTEXT(&ret, &pp, str->length)) {
        ASN1_STRING_print_ex(bio, ret, ASN1_STRFLGS_UTF8_CONVERT);
        rv = 1;
    }

    ASN1_STRING_free(ret);
    return rv;
}