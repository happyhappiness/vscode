static int apr_ldap_rebind_set_callback(LDAP *ld)
{
#if defined(LDAP_SET_REBIND_PROC_THREE)
    ldap_set_rebind_proc(ld, LDAP_rebindproc, NULL);
#else
    ldap_set_rebind_proc(ld, LDAP_rebindproc);
#endif
    return APR_SUCCESS;
}