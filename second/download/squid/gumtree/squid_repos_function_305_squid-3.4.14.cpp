int
get_memberof(struct main_args *margs, char *user, char *domain, char *group)
{
    LDAP *ld = NULL;
    LDAPMessage *res;
#ifndef HAVE_SUN_LDAP_SDK
    int ldap_debug = 0;
#endif
    struct ldap_creds *lcreds = NULL;
    char *bindp = NULL;
    char *filter = NULL;
    char *search_exp;
    struct timeval searchtime;
    int rc = 0, kc = 1;
    int retval;
    char **attr_value = NULL;
    size_t max_attr = 0;
    struct hstruct *hlist = NULL;
    size_t nhosts = 0;
    char *ldap_filter_esc = NULL;

    searchtime.tv_sec = SEARCH_TIMEOUT;
    searchtime.tv_usec = 0;
    /*
     * Fill Kerberos memory cache with credential from keytab for SASL/GSSAPI
     */
    if (domain) {
        debug((char *) "%s| %s: DEBUG: Setup Kerberos credential cache\n", LogTime(), PROGRAM);

#ifdef HAVE_KRB5
        kc = krb5_create_cache(domain);
        if (kc) {
            error((char *) "%s| %s: ERROR: Error during setup of Kerberos credential cache\n", LogTime(), PROGRAM);
        }
#else
        kc = 1;
        debug((char *) "%s| %s: DEBUG: Kerberos is not supported. Use username/passwaord with ldap url instead\n", LogTime(), PROGRAM);
#endif
    }

    if (kc && (!margs->lurl || !margs->luser || !margs->lpass)) {
        /*
         * If Kerberos fails and no url given exit here
         */
        retval = 0;
        goto cleanup;
    }
#ifndef HAVE_SUN_LDAP_SDK
    /*
     * Initialise ldap
     */
    ldap_debug = 127 /* LDAP_DEBUG_TRACE */ ;
    ldap_debug = -1 /* LDAP_DEBUG_ANY */ ;
    ldap_debug = 0;
    (void) ldap_set_option(NULL, LDAP_OPT_DEBUG_LEVEL, &ldap_debug);
#endif
    debug((char *) "%s| %s: DEBUG: Initialise ldap connection\n", LogTime(), PROGRAM);

    if (domain && !kc) {
        if (margs->ssl) {
            debug((char *) "%s| %s: DEBUG: Enable SSL to ldap servers\n", LogTime(), PROGRAM);
        }
        debug((char *) "%s| %s: DEBUG: Canonicalise ldap server name for domain %s\n", LogTime(), PROGRAM, domain);
        /*
         * Loop over list of ldap servers of users domain
         */
        nhosts = get_ldap_hostname_list(margs, &hlist, 0, domain);
        for (size_t i = 0; i < nhosts; ++i) {
            int port = 389;
            if (hlist[i].port != -1)
                port = hlist[i].port;
            debug((char *) "%s| %s: DEBUG: Setting up connection to ldap server %s:%d\n", LogTime(), PROGRAM, hlist[i].host, port);

            ld = tool_ldap_open(margs, hlist[i].host, port, margs->ssl);
            if (!ld)
                continue;

            /*
             * ldap bind with SASL/GSSAPI authentication (only possible if a domain was part of the username)
             */

#if defined(HAVE_SASL_H) || defined(HAVE_SASL_SASL_H) || defined(HAVE_SASL_DARWIN)
            debug((char *) "%s| %s: DEBUG: Bind to ldap server with SASL/GSSAPI\n", LogTime(), PROGRAM);

            rc = tool_sasl_bind(ld, bindp, margs->ssl);
            if (rc != LDAP_SUCCESS) {
                error((char *) "%s| %s: ERROR: Error while binding to ldap server with SASL/GSSAPI: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
                ldap_unbind(ld);
                ld = NULL;
                continue;
            }
            lcreds = (ldap_creds *) xmalloc(sizeof(struct ldap_creds));
            lcreds->dn = NULL;
            lcreds->pw = margs->ssl ? xstrdup(margs->ssl) : NULL;
            ldap_set_rebind_proc(ld, ldap_sasl_rebind, (char *) lcreds);
            if (ld != NULL) {
                debug((char *) "%s| %s: DEBUG: %s initialised %sconnection to ldap server %s:%d\n", LogTime(), PROGRAM, ld ? "Successfully" : "Failed to", margs->ssl ? "SSL protected " : "", hlist[i].host, port);
                break;
            }
#else
            ldap_unbind(ld);
            ld = NULL;
            error((char *) "%s| %s: ERROR: SASL not supported on system\n", LogTime(), PROGRAM);
            continue;
#endif
        }
        nhosts = free_hostname_list(&hlist, nhosts);
        if (ld == NULL) {
            debug((char *) "%s| %s: DEBUG: Error during initialisation of ldap connection: %s\n", LogTime(), PROGRAM, strerror(errno));
        }
        bindp = convert_domain_to_bind_path(domain);
    }
    if ((!domain || !ld) && margs->lurl && strstr(margs->lurl, "://")) {
        char *hostname;
        char *host;
        int port;
        char *ssl = NULL;
        char *p;
        /*
         * If username does not contain a domain and a url was given then try it
         */
        hostname = strstr(margs->lurl, "://") + 3;
        ssl = strstr(margs->lurl, "ldaps://");
        if (ssl) {
            debug((char *) "%s| %s: DEBUG: Enable SSL to ldap servers\n", LogTime(), PROGRAM);
        }
        debug((char *) "%s| %s: DEBUG: Canonicalise ldap server name %s\n", LogTime(), PROGRAM, hostname);
        /*
         * Loop over list of ldap servers
         */
        host = xstrdup(hostname);
        port = 389;
        if ((p = strchr(host, ':'))) {
            *p = '\0';
            ++p;
            port = atoi(p);
        }
        nhosts = get_hostname_list(&hlist, 0, host);
        xfree(host);
        for (size_t i = 0; i < nhosts; ++i) {

            ld = tool_ldap_open(margs, hlist[i].host, port, ssl);
            if (!ld)
                continue;
            /*
             * ldap bind with username/password authentication
             */

            debug((char *) "%s| %s: DEBUG: Bind to ldap server with Username/Password\n", LogTime(), PROGRAM);
            rc = ldap_simple_bind_s(ld, margs->luser, margs->lpass);
            if (rc != LDAP_SUCCESS) {
                error((char *) "%s| %s: ERROR: Error while binding to ldap server with Username/Password: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
                ldap_unbind(ld);
                ld = NULL;
                continue;
            }
            lcreds = (ldap_creds *) xmalloc(sizeof(struct ldap_creds));
            lcreds->dn = xstrdup(margs->luser);
            lcreds->pw = xstrdup(margs->lpass);
            ldap_set_rebind_proc(ld, ldap_simple_rebind, (char *) lcreds);
            debug((char *) "%s| %s: DEBUG: %s set up %sconnection to ldap server %s:%d\n", LogTime(), PROGRAM, ld ? "Successfully" : "Failed to", ssl ? "SSL protected " : "", hlist[i].host, port);
            break;

        }
        nhosts = free_hostname_list(&hlist, nhosts);
        xfree(bindp);
        if (margs->lbind) {
            bindp = xstrdup(margs->lbind);
        } else {
            bindp = convert_domain_to_bind_path(domain);
        }
    }
    if (ld == NULL) {
        debug((char *) "%s| %s: DEBUG: Error during initialisation of ldap connection: %s\n", LogTime(), PROGRAM, strerror(errno));
        retval = 0;
        goto cleanup;
    }
    /*
     * ldap search for user
     */
    /*
     * Check if server is AD by querying for attribute samaccountname
     */
    margs->AD = 0;
    rc = check_AD(margs, ld);
    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error determining ldap server type: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        ldap_unbind(ld);
        ld = NULL;
        retval = 0;
        goto cleanup;
    }
    if (margs->AD)
        filter = (char *) FILTER_AD;
    else
        filter = (char *) FILTER;

    ldap_filter_esc = escape_filter(user);

    search_exp = (char *) xmalloc(strlen(filter) + strlen(ldap_filter_esc) + 1);
    snprintf(search_exp, strlen(filter) + strlen(ldap_filter_esc) + 1, filter, ldap_filter_esc);

    xfree(ldap_filter_esc);

    debug((char *) "%s| %s: DEBUG: Search ldap server with bind path %s and filter : %s\n", LogTime(), PROGRAM, bindp, search_exp);
    rc = ldap_search_ext_s(ld, bindp, LDAP_SCOPE_SUBTREE,
                           search_exp, NULL, 0,
                           NULL, NULL, &searchtime, 0, &res);
    xfree(search_exp);

    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error searching ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
        ldap_unbind(ld);
        ld = NULL;
        retval = 0;
        goto cleanup;
    }
    debug((char *) "%s| %s: DEBUG: Found %d ldap entr%s\n", LogTime(), PROGRAM, ldap_count_entries(ld, res), ldap_count_entries(ld, res) > 1 || ldap_count_entries(ld, res) == 0 ? "ies" : "y");

    if (ldap_count_entries(ld, res) != 0) {

        if (margs->AD)
            max_attr = get_attributes(ld, res, ATTRIBUTE_AD, &attr_value);
        else {
            max_attr = get_attributes(ld, res, ATTRIBUTE, &attr_value);
        }

        /*
         * Compare group names
         */
        retval = 0;
        for (size_t k = 0; k < max_attr; ++k) {
            char *av = NULL;

            /* Compare first CN= value assuming it is the same as the group name itself */
            av = attr_value[k];
            if (!strncasecmp("CN=", av, 3)) {
                char *avp = NULL;
                av += 3;
                if ((avp = strchr(av, ','))) {
                    *avp = '\0';
                }
            }
            if (debug_enabled) {
                debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " \"%s\" in hex UTF-8 is ", LogTime(), PROGRAM, k + 1, av);
                for (unsigned int n = 0; av[n] != '\0'; ++n)
                    fprintf(stderr, "%02x", (unsigned char) av[n]);
                fprintf(stderr, "\n");
            }
            if (!strcasecmp(group, av)) {
                retval = 1;
                if (debug_enabled)
                    debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " \"%s\" matches group name \"%s\"\n", LogTime(), PROGRAM, k + 1, av, group);
                else
                    break;
            } else
                debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " \"%s\" does not match group name \"%s\"\n", LogTime(), PROGRAM, k + 1, av, group);
        }
        /*
         * Do recursive group search for AD only since posixgroups can not contain other groups
         */
        if (!retval && margs->AD) {
            if (debug_enabled && max_attr > 0) {
                debug((char *) "%s| %s: DEBUG: Perform recursive group search\n", LogTime(), PROGRAM);
            }
            for (size_t j = 0; j < max_attr; ++j) {
                char *av = NULL;

                av = attr_value[j];
                if (search_group_tree(margs, ld, bindp, av, group, 1)) {
                    retval = 1;
                    if (!strncasecmp("CN=", av, 3)) {
                        char *avp = NULL;
                        av += 3;
                        if ((avp = strchr(av, ','))) {
                            *avp = '\0';
                        }
                    }
                    if (debug_enabled)
                        debug((char *) "%s| %s: DEBUG: Entry %" PRIuSIZE " group \"%s\" is (in)direct member of group \"%s\"\n", LogTime(), PROGRAM, j + 1, av, group);
                    else
                        break;
                }
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
    } else if (ldap_count_entries(ld, res) == 0 && margs->AD) {
        ldap_msgfree(res);
        ldap_unbind(ld);
        ld = NULL;
        retval = 0;
        goto cleanup;
    } else {
        ldap_msgfree(res);
        retval = 0;
    }

    if (!margs->AD && retval == 0) {
        /*
         * Check for primary Group membership
         */
        debug((char *) "%s| %s: DEBUG: Search for primary group membership: \"%s\"\n", LogTime(), PROGRAM, group);
        filter = (char *) FILTER_UID;

        ldap_filter_esc = escape_filter(user);

        search_exp = (char *) xmalloc(strlen(filter) + strlen(ldap_filter_esc) + 1);
        snprintf(search_exp, strlen(filter) + strlen(ldap_filter_esc) + 1, filter, ldap_filter_esc);

        xfree(ldap_filter_esc);

        debug((char *) "%s| %s: DEBUG: Search ldap server with bind path %s and filter: %s\n", LogTime(), PROGRAM, bindp, search_exp);
        rc = ldap_search_ext_s(ld, bindp, LDAP_SCOPE_SUBTREE,
                               search_exp, NULL, 0,
                               NULL, NULL, &searchtime, 0, &res);
        xfree(search_exp);

        debug((char *) "%s| %s: DEBUG: Found %d ldap entr%s\n", LogTime(), PROGRAM, ldap_count_entries(ld, res), ldap_count_entries(ld, res) > 1 || ldap_count_entries(ld, res) == 0 ? "ies" : "y");

        max_attr = get_attributes(ld, res, ATTRIBUTE_GID, &attr_value);

        if (max_attr == 1) {
            char **attr_value_2 = NULL;
            size_t max_attr_2 = 0;

            ldap_msgfree(res);
            filter = (char *) FILTER_GID;

            ldap_filter_esc = escape_filter(attr_value[0]);

            search_exp = (char *) xmalloc(strlen(filter) + strlen(ldap_filter_esc) + 1);
            snprintf(search_exp, strlen(filter) + strlen(ldap_filter_esc) + 1, filter, ldap_filter_esc);

            xfree(ldap_filter_esc);

            debug((char *) "%s| %s: DEBUG: Search ldap server with bind path %s and filter: %s\n", LogTime(), PROGRAM, bindp, search_exp);
            rc = ldap_search_ext_s(ld, bindp, LDAP_SCOPE_SUBTREE,
                                   search_exp, NULL, 0,
                                   NULL, NULL, &searchtime, 0, &res);
            xfree(search_exp);

            max_attr_2 = get_attributes(ld, res, ATTRIBUTE, &attr_value_2);
            /*
             * Compare group names
             */
            retval = 0;
            if (max_attr_2 == 1) {
                /* Compare first CN= value assuming it is the same as the group name itself */
                char *av = attr_value_2[0];
                if (!strcasecmp(group, av)) {
                    retval = 1;
                    debug((char *) "%s| %s: DEBUG: \"%s\" matches group name \"%s\"\n", LogTime(), PROGRAM, av, group);
                } else
                    debug((char *) "%s| %s: DEBUG: \"%s\" does not match group name \"%s\"\n", LogTime(), PROGRAM, av, group);

            }
            /*
             * Cleanup
             */
            if (attr_value_2) {
                size_t j;
                for (j = 0; j < max_attr_2; ++j) {
                    xfree(attr_value_2[j]);
                }
                safe_free(attr_value_2);
            }
            ldap_msgfree(res);

            debug((char *) "%s| %s: DEBUG: Users primary group %s %s\n", LogTime(), PROGRAM, retval ? "matches" : "does not match", group);

        } else {
            ldap_msgfree(res);
            debug((char *) "%s| %s: DEBUG: Did not find ldap entry for group %s\n", LogTime(), PROGRAM, group);
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
    }
    rc = ldap_unbind(ld);
    ld = NULL;
    if (rc != LDAP_SUCCESS) {
        error((char *) "%s| %s: ERROR: Error unbind ldap server: %s\n", LogTime(), PROGRAM, ldap_err2string(rc));
    }
    debug((char *) "%s| %s: DEBUG: Unbind ldap server\n", LogTime(), PROGRAM);
cleanup:
#ifdef HAVE_KRB5
    if (domain)
        krb5_cleanup();
#endif
    if (lcreds) {
        xfree(lcreds->dn);
        xfree(lcreds->pw);
        xfree(lcreds);
    }
    xfree(bindp);
    return (retval);
}