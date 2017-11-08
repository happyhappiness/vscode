static char *asn1_string_to_utf8(apr_pool_t *p, ASN1_STRING *asn1str)
{
    char *result = NULL;
    BIO *bio;
    int len;

    if ((bio = BIO_new(BIO_s_mem())) == NULL)
        return NULL;

    ASN1_STRING_print_ex(bio, asn1str, ASN1_STRFLGS_ESC_CTRL|
                                       ASN1_STRFLGS_UTF8_CONVERT);
    len = BIO_pending(bio);
    if (len > 0) {
        result = apr_palloc(p, len+1);
        len = BIO_read(bio, result, len);
        result[len] = NUL;
    }
    BIO_free(bio);
    return result;
}