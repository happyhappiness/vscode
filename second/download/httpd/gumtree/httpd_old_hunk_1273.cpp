        /* Set the alias dereferencing option */
        ldap_set_option(ldc->ldap, LDAP_OPT_DEREF, &(ldc->deref));

        /* always default to LDAP V3 */
        ldap_set_option(ldc->ldap, LDAP_OPT_PROTOCOL_VERSION, &version);

    }


    /* loop trying to bind up to 10 times if LDAP_SERVER_DOWN error is
     * returned.  Break out of the loop on Success or any other error.
     *
