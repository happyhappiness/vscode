static apr_status_t apr_ldap_rebind_remove_helper(void *data)
{
    LDAP *ld = (LDAP *)data;
    apr_ldap_rebind_remove(ld);
    return APR_SUCCESS;
}