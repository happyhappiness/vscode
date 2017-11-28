int
tool_sasl_bind(LDAP * ld, char *binddn, char *ssl)
{
    /*
     * unsigned sasl_flags = LDAP_SASL_AUTOMATIC;
     * unsigned sasl_flags = LDAP_SASL_QUIET;
     */
    /*
     * Avoid SASL messages
     */
#if HAVE_SUN_LDAP_SDK
    unsigned sasl_flags = LDAP_SASL_INTERACTIVE;
#else
    unsigned sasl_flags = LDAP_SASL_QUIET;
#endif
    char *sasl_realm = NULL;
    char *sasl_authc_id = NULL;
    char *sasl_authz_id = NULL;
    char *sasl_mech = (char *) "GSSAPI";
    /*
     * Force encryption
     */
    char *sasl_secprops;
    /*
     * char  *sasl_secprops = (char *)"maxssf=56";
     * char  *sasl_secprops = NULL;
     */
    struct berval passwd = {0, NULL};
    void *defaults;
    int rc = LDAP_SUCCESS;

    if (ssl)
        sasl_secprops = (char *) "maxssf=0";
    else
        sasl_secprops = (char *) "maxssf=56";
    /*      sasl_secprops = (char *)"maxssf=0"; */
    /*      sasl_secprops = (char *)"maxssf=56"; */

    if (sasl_secprops != NULL) {
        rc = ldap_set_option(ld, LDAP_OPT_X_SASL_SECPROPS,
                             (void *) sasl_secprops);
        if (rc != LDAP_SUCCESS) {
            error((char *) "%s| %s: ERROR: Could not set LDAP_OPT_X_SASL_SECPROPS: %s: %s\n", LogTime(), PROGRAM, sasl_secprops, ldap_err2string(rc));
            return rc;
        }
    }
    defaults = lutil_sasl_defaults(ld,
                                   sasl_mech,
                                   sasl_realm,
                                   sasl_authc_id,
                                   passwd.bv_val,
                                   sasl_authz_id);

    rc = ldap_sasl_interactive_bind_s(ld, binddn,
                                      sasl_mech, NULL, NULL,
                                      sasl_flags, lutil_sasl_interact, defaults);

    lutil_sasl_freedefs(defaults);
    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: ldap_sasl_interactive_bind_s error: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
    }
    return rc;
}