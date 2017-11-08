static int uldap_ld_errno(util_ldap_connection_t *ldc)
{
    int ldaprc;
#ifdef LDAP_OPT_ERROR_NUMBER
    if (LDAP_SUCCESS == ldap_get_option(ldc->ldap, LDAP_OPT_ERROR_NUMBER, &ldaprc)) return ldaprc;
#endif
#ifdef LDAP_OPT_RESULT_CODE
    if (LDAP_SUCCESS == ldap_get_option(ldc->ldap, LDAP_OPT_RESULT_CODE, &ldaprc)) return ldaprc;
#endif
    return LDAP_OTHER;
}