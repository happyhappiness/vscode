static int
searchLDAPGroup(LDAP * ld, const char *group, const char *member, const char *extension_dn)
{
    std::string filter;
    LDAPMessage *res = NULL;
    int rc;
    char *searchattr[] = {(char *) LDAP_NO_ATTRS, NULL};

    const std::string searchbase = build_searchbase(extension_dn, basedn);
    if (!build_filter(filter, searchfilter, member, group)) {
        std::cerr << PROGRAM_NAME  << ": ERROR: Failed to construct LDAP search filter. filter=\"" <<
                  filter.c_str() << "\", user=\"" << member << "\", group=\"" << group << "\"" << std::endl;
        return -1;
    }
    debug("group filter '%s', searchbase '%s'\n", filter.c_str(), searchbase.c_str());

    rc = ldap_search_s(ld, searchbase.c_str(), searchscope, filter.c_str(), searchattr, 1, &res);
    LdapResult ldapRes(res, ldap_msgfree);
    if (!ldap_search_ok(rc))
        return -1;

    return ldap_first_entry(ld, ldapRes.get()) ? 0 : 1;
}