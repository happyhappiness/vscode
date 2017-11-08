static int apr_ldap_rebind_set_callback(LDAP *ld)
{
    ldap_set_rebind_proc(ld, LDAP_rebindproc);
    return APR_SUCCESS;
}