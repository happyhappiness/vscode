static apr_status_t uldap_connection_unbind(void *param)
{
    util_ldap_connection_t *ldc = param;

    if (ldc) {
        if (ldc->ldap) {
            ldap_unbind_s(ldc->ldap);
            ldc->ldap = NULL;
        }
        ldc->bound = 0;
    }

    return APR_SUCCESS;
}