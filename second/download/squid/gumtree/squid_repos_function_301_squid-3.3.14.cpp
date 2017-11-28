int
search_group_tree(struct main_args *margs, LDAP * ld, char *bindp, char *ldap_group, char *group, int depth)
{
    LDAPMessage *res = NULL;
    char **attr_value = NULL;
    int max_attr = 0;
    char *filter = NULL;
    char *search_exp = NULL;
    int j, rc = 0, retval = 0;
    char *av = NULL, *avp = NULL;
    int ldepth;
    char *ldap_filter_esc = NULL;
    struct timeval searchtime;

#define FILTER_GROUP_AD "(&(%s)(objectclass=group))"
#define FILTER_GROUP "(&(memberuid=%s)(objectclass=posixgroup))"

    searchtime.tv_sec = SEARCH_TIMEOUT;
    searchtime.tv_usec = 0;

    if (margs->AD)
        filter = (char *) FILTER_GROUP_AD;
    else
        filter = (char *) FILTER_GROUP;

    ldap_filter_esc = escape_filter(ldap_group);

    search_exp = (char *) xmalloc(strlen(filter) + strlen(ldap_filter_esc) + 1);
    snprintf(search_exp, strlen(filter) + strlen(ldap_filter_esc) + 1, filter, ldap_filter_esc);

    xfree(ldap_filter_esc);

    if (depth > margs->mdepth) {
        debug((char *) "%s| %s: DEBUG: Max search depth reached %d>%d\n", LogTime(), PROGRAM, depth, margs->mdepth);
        xfree(search_exp);
        return 0;
    }
    debug((char *) "%s| %s: DEBUG: Search ldap server with bind path %s and filter : %s\n", LogTime(), PROGRAM, bindp, search_exp);
    rc = ldap_search_ext_s(ld, bindp, LDAP_SCOPE_SUBTREE,
                           search_exp, NULL, 0,
                           NULL, NULL, &searchtime, 0, &res);
    xfree(search_exp);

    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error searching ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        ldap_unbind_s(ld);
        return 0;
    }
    debug((char *) "%s| %s: DEBUG: Found %d ldap entr%s\n", LogTime(), PROGRAM, ldap_count_entries(ld, res), ldap_count_entries(ld, res) > 1 || ldap_count_entries(ld, res) == 0 ? "ies" : "y");

    if (margs->AD)
        max_attr = get_attributes(margs, ld, res, ATTRIBUTE_AD, &attr_value);
    else
        max_attr = get_attributes(margs, ld, res, ATTRIBUTE, &attr_value);

    /*
     * Compare group names
     */
    retval = 0;
    ldepth = depth + 1;
    for (j = 0; j < max_attr; ++j) {

        /* Compare first CN= value assuming it is the same as the group name itself */
        av = attr_value[j];
        if (!strncasecmp("CN=", av, 3)) {
            av += 3;
            if ((avp = strchr(av, ','))) {
                *avp = '\0';
            }
        }
        if (debug_enabled) {
            int n;
            debug((char *) "%s| %s: DEBUG: Entry %d \"%s\" in hex UTF-8 is ", LogTime(), PROGRAM, j + 1, av);
            for (n = 0; av[n] != '\0'; ++n)
                fprintf(stderr, "%02x", (unsigned char) av[n]);
            fprintf(stderr, "\n");
        }
        if (!strcasecmp(group, av)) {
            retval = 1;
            debug((char *) "%s| %s: DEBUG: Entry %d \"%s\" matches group name \"%s\"\n", LogTime(), PROGRAM, j + 1, av, group);
            break;
        } else
            debug((char *) "%s| %s: DEBUG: Entry %d \"%s\" does not match group name \"%s\"\n", LogTime(), PROGRAM, j + 1, av, group);
        /*
         * Do recursive group search
         */
        debug((char *) "%s| %s: DEBUG: Perform recursive group search for group \"%s\"\n", LogTime(), PROGRAM, av);
        av = attr_value[j];
        if (search_group_tree(margs, ld, bindp, av, group, ldepth)) {
            retval = 1;
            if (!strncasecmp("CN=", av, 3)) {
                av += 3;
                if ((avp = strchr(av, ','))) {
                    *avp = '\0';
                }
            }
            if (debug_enabled)
                debug((char *) "%s| %s: DEBUG: Entry %d \"%s\" is member of group named \"%s\"\n", LogTime(), PROGRAM, j + 1, av, group);
            else
                break;

        }
    }

    /*
     * Cleanup
     */
    if (attr_value) {
        for (j = 0; j < max_attr; ++j) {
            xfree(attr_value[j]);
        }
        xfree(attr_value);
        attr_value = NULL;
    }
    ldap_msgfree(res);

    return retval;
}