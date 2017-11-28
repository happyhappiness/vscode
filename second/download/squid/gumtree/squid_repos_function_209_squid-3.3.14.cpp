static int
searchLDAPGroup(LDAP * ld, char *group, char *member, char *extension_dn)
{
    char filter[256];
    static char searchbase[256];
    LDAPMessage *res = NULL;
    LDAPMessage *entry;
    int rc;
    char *searchattr[] = {(char *) LDAP_NO_ATTRS, NULL};

    if (extension_dn && *extension_dn)
        snprintf(searchbase, sizeof(searchbase), "%s,%s", extension_dn, basedn);
    else
        snprintf(searchbase, sizeof(searchbase), "%s", basedn);

    if (build_filter(filter, sizeof(filter), searchfilter, member, group) != 0) {
        fprintf(stderr, PROGRAM_NAME ": ERROR: Failed to construct LDAP search filter. filter=\"%s\", user=\"%s\", group=\"%s\"\n", filter, member, group);
        return 1;
    }
    debug("group filter '%s', searchbase '%s'\n", filter, searchbase);

    rc = ldap_search_s(ld, searchbase, searchscope, filter, searchattr, 1, &res);
    if (rc != LDAP_SUCCESS) {
        if (noreferrals && rc == LDAP_PARTIAL_RESULTS) {
            /* Everything is fine. This is expected when referrals
             * are disabled.
             */
        } else {
            fprintf(stderr, PROGRAM_NAME ": WARNING: LDAP search error '%s'\n", ldap_err2string(rc));
#if defined(NETSCAPE_SSL)
            if (sslpath && ((rc == LDAP_SERVER_DOWN) || (rc == LDAP_CONNECT_ERROR))) {
                int sslerr = PORT_GetError();
                fprintf(stderr, PROGRAM_NAME ": WARNING: SSL error %d (%s)\n", sslerr, ldapssl_err2string(sslerr));
            }
#endif
            ldap_msgfree(res);
            return 1;
        }
    }
    entry = ldap_first_entry(ld, res);
    if (!entry) {
        ldap_msgfree(res);
        return 1;
    }
    ldap_msgfree(res);
    return 0;
}