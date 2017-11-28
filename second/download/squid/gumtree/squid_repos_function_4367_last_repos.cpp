static int
searchLDAP(LDAP * ld, char *group, char *login, char *extension_dn)
{

    const char *current_userdn = userbasedn ? userbasedn : basedn;
    if (usersearchfilter) {
        LDAPMessage *res = NULL;
        LDAPMessage *entry;
        int rc;
        char *userdn;
        char *searchattr[] = {(char *) LDAP_NO_ATTRS, NULL};
        const std::string searchbase = build_searchbase(extension_dn, current_userdn);
        std::string filter(usersearchfilter);
        const std::string escaped_login = ldap_escape_value(login);
        formatWithString(filter, escaped_login);

        debug("user filter '%s', searchbase '%s'\n", filter.c_str(), searchbase.c_str());
        rc = ldap_search_s(ld, searchbase.c_str(), searchscope, filter.c_str(), searchattr, 1, &res);
        LdapResult ldapRes(res, ldap_msgfree);
        if (!ldap_search_ok(rc))
            return -1;
        entry = ldap_first_entry(ld, ldapRes.get());
        if (!entry) {
            std::cerr << PROGRAM_NAME << ": WARNING: User '" << login <<
                      " not found in '" << searchbase.c_str() << "'" << std::endl;
            return 1;
        }
        userdn = ldap_get_dn(ld, entry);
        rc = searchLDAPGroup(ld, group, userdn, extension_dn);
        squid_ldap_memfree(userdn);
        return rc;
    } else if (userdnattr) {
        std::stringstream str;
        str << userdnattr << "=" << login << ", ";
        if (extension_dn && *extension_dn)
            str << extension_dn << ", ";
        str << current_userdn;
        return searchLDAPGroup(ld, group, str.str().c_str(), extension_dn);
    } else {
        return searchLDAPGroup(ld, group, login, extension_dn);
    }
}