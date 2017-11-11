static int compare_client_certs(apr_array_header_t *srcs,
                                apr_array_header_t *dests)
{
    int i = 0;
    struct apr_ldap_opt_tls_cert_t *src, *dest;

    /* arrays both NULL? if so, then equal */
    if (srcs == NULL && dests == NULL) {
        return 0;
    }

    /* arrays different length or either NULL? If so, then not equal */
    if (srcs == NULL || dests == NULL || srcs->nelts != dests->nelts) {
        return 1;
    }

    /* run an actual comparison */
    src = (struct apr_ldap_opt_tls_cert_t *)srcs->elts;
    dest = (struct apr_ldap_opt_tls_cert_t *)dests->elts;
    for (i = 0; i < srcs->nelts; i++) {
        if ((strcmp(src[i].path, dest[i].path)) ||
            (src[i].type != dest[i].type) ||
            /* One is passwordless? If so, then not equal */
            ((src[i].password == NULL) ^ (dest[i].password == NULL)) ||
            (src[i].password != NULL && dest[i].password != NULL &&
             strcmp(src[i].password, dest[i].password))) {
            return 1;
        }
    }

    /* if we got here, the cert arrays were identical */
    return 0;

}