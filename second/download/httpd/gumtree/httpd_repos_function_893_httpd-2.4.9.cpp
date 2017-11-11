static const char *extract_responder_uri(X509 *cert, apr_pool_t *pool)
{
    STACK_OF(ACCESS_DESCRIPTION) *values;
    char *result = NULL;
    int j;

    values = X509_get_ext_d2i(cert, NID_info_access, NULL, NULL);
    if (!values) {
        return NULL;
    }

    for (j = 0; j < sk_ACCESS_DESCRIPTION_num(values) && !result; j++) {
        ACCESS_DESCRIPTION *value = sk_ACCESS_DESCRIPTION_value(values, j);

        /* Name found in extension, and is a URI: */
        if (OBJ_obj2nid(value->method) == NID_ad_OCSP
            && value->location->type == GEN_URI) {
            result = apr_pstrdup(pool,
                                 (char *)value->location->d.uniformResourceIdentifier->data);
        }
    }

    AUTHORITY_INFO_ACCESS_free(values);

    return result;
}