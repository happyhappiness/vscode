int
check_AD(struct main_args *margs, LDAP * ld)
{
    LDAPMessage *res;
    char **attr_value = NULL;
    struct timeval searchtime;
    size_t max_attr = 0;
    int rc = 0;

#define FILTER_SCHEMA "(objectclass=*)"
#define ATTRIBUTE_SCHEMA "schemaNamingContext"
#define FILTER_SAM "(ldapdisplayname=samaccountname)"

    searchtime.tv_sec = SEARCH_TIMEOUT;
    searchtime.tv_usec = 0;

    debug((char *) "%s| %s: DEBUG: Search ldap server with bind path \"\" and filter: %s\n", LogTime(), PROGRAM, FILTER_SCHEMA);
    rc = ldap_search_ext_s(ld, (char *) "", LDAP_SCOPE_BASE, (char *) FILTER_SCHEMA, NULL, 0,
                           NULL, NULL, &searchtime, 0, &res);

    if (rc == LDAP_SUCCESS)
        max_attr = get_attributes(ld, res, ATTRIBUTE_SCHEMA, &attr_value);

    if (max_attr == 1) {
        ldap_msgfree(res);
        debug((char *) "%s| %s: DEBUG: Search ldap server with bind path %s and filter: %s\n", LogTime(), PROGRAM, attr_value[0], FILTER_SAM);
        rc = ldap_search_ext_s(ld, attr_value[0], LDAP_SCOPE_SUBTREE, (char *) FILTER_SAM, NULL, 0,
                               NULL, NULL, &searchtime, 0, &res);
        debug((char *) "%s| %s: DEBUG: Found %d ldap entr%s\n", LogTime(), PROGRAM, ldap_count_entries(ld, res), ldap_count_entries(ld, res) > 1 || ldap_count_entries(ld, res) == 0 ? "ies" : "y");
        if (ldap_count_entries(ld, res) > 0)
            margs->AD = 1;
    } else
        debug((char *) "%s| %s: DEBUG: Did not find ldap entry for subschemasubentry\n", LogTime(), PROGRAM);
    debug((char *) "%s| %s: DEBUG: Determined ldap server %sas an Active Directory server\n", LogTime(), PROGRAM, margs->AD ? "" : "not ");
    /*
     * Cleanup
     */
    if (attr_value) {
        size_t j;
        for (j = 0; j < max_attr; ++j) {
            xfree(attr_value[j]);
        }
        safe_free(attr_value);
    }
    ldap_msgfree(res);
    return rc;
}