static apr_status_t authnz_ldap_cleanup_connection_close(void *param)
{
    util_ldap_connection_t *ldc = param;
    util_ldap_connection_close(ldc);
    return APR_SUCCESS;
}