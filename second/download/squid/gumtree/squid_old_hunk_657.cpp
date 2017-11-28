                squid_ldap_set_timelimit(ld, timelimit);
                squid_ldap_set_referrals(ld, !noreferrals);
                squid_ldap_set_aliasderef(ld, aliasderef);
                if (binddn && bindpasswd && *binddn && *bindpasswd) {
                    rc = ldap_simple_bind_s(ld, binddn, bindpasswd);
                    if (rc != LDAP_SUCCESS) {
                        fprintf(stderr, PROGRAM_NAME ": WARNING: could not bind to binddn '%s'\n", ldap_err2string(rc));
                        ldap_unbind(ld);
                        ld = NULL;
                        break;
                    }
                }
                debug("Connected OK\n");
            }
            if (searchLDAP(ld, group, user, extension_dn) == 0) {
                found = 1;
                break;
            } else {
                if (tryagain) {
                    tryagain = 0;
                    ldap_unbind(ld);
                    ld = NULL;
                    goto recover;
                }
            }
        }
        if (found)
            SEND_OK("");
        else {
            SEND_ERR("");
        }

        if (ld != NULL) {
            if (!persistent || (squid_ldap_errno(ld) != LDAP_SUCCESS && squid_ldap_errno(ld) != LDAP_INVALID_CREDENTIALS)) {
