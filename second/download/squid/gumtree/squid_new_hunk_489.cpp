        ldap_unbind_s(ld);
        return 0;
    }
    debug((char *) "%s| %s: DEBUG: Found %d ldap entr%s\n", LogTime(), PROGRAM, ldap_count_entries(ld, res), ldap_count_entries(ld, res) > 1 || ldap_count_entries(ld, res) == 0 ? "ies" : "y");

    if (margs->AD)
        max_attr = get_attributes(ld, res, ATTRIBUTE_AD, &attr_value);
    else
        max_attr = get_attributes(ld, res, ATTRIBUTE, &attr_value);

    /*
     * Compare group names
     */
    retval = 0;
    ldepth = depth + 1;
    for (size_t j = 0; j < max_attr; ++j) {
        char *av = NULL;

        /* Compare first CN= value assuming it is the same as the group name itself */
        av = attr_value[j];
        if (!strncasecmp("CN=", av, 3)) {
            char *avp = NULL;
            av += 3;
            if ((avp = strchr(av, ','))) {
                *avp = '\0';
            }
        }
        if (debug_enabled) {
            int n;
            debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " \"%s\" in hex UTF-8 is ", LogTime(), PROGRAM, j + 1, av);
            for (n = 0; av[n] != '\0'; ++n)
                fprintf(stderr, "%02x", (unsigned char) av[n]);
            fprintf(stderr, "\n");
        }
        if (!strcasecmp(group, av)) {
            retval = 1;
            debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " \"%s\" matches group name \"%s\"\n", LogTime(), PROGRAM, j + 1, av, group);
            break;
        } else
            debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " \"%s\" does not match group name \"%s\"\n", LogTime(), PROGRAM, j + 1, av, group);
        /*
         * Do recursive group search
         */
        debug((char *) "%s| %s: DEBUG: Perform recursive group search for group \"%s\"\n", LogTime(), PROGRAM, av);
        av = attr_value[j];
        if (search_group_tree(margs, ld, bindp, av, group, ldepth)) {
            retval = 1;
            if (!strncasecmp("CN=", av, 3)) {
                char *avp = NULL;
                av += 3;
                if ((avp = strchr(av, ','))) {
                    *avp = '\0';
                }
            }
            if (debug_enabled)
                debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " \"%s\" is member of group named \"%s\"\n", LogTime(), PROGRAM, j + 1, av, group);
            else
                break;

        }
    }

    /*
     * Cleanup
     */
    if (attr_value) {
        for (size_t j = 0; j < max_attr; ++j) {
            xfree(attr_value[j]);
        }
        safe_free(attr_value);
    }
    ldap_msgfree(res);

    return retval;
}

int
ldap_set_defaults(LDAP * ld)
{
    int val, rc = 0;
#ifdef LDAP_OPT_NETWORK_TIMEOUT
    struct timeval tv;
#endif
    val = LDAP_VERSION3;
