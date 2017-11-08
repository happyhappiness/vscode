static int apr_ldap_rebind_set_callback(LDAP *ld)
{
    ldap_set_rebind_proc(ld, (LDAPRebindProc)LDAP_rebindproc);
    return APR_SUCCESS;
}