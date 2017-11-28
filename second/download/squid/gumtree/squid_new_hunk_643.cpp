        switch (option) {
        case 'H':
#if !HAS_URI_SUPPORT
            fprintf(stderr, "ERROR: Your LDAP library does not have URI support\n");
            return 1;
#endif
        /* Fall thru to -h */
        case 'h':
            if (ldapServer) {
                int len = strlen(ldapServer) + 1 + strlen(value) + 1;
                char *newhost = static_cast<char*>(xmalloc(len));
                snprintf(newhost, len, "%s %s", ldapServer, value);
                free(ldapServer);
                ldapServer = newhost;
            } else {
                ldapServer = xstrdup(value);
            }
