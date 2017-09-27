*/

    /*
     * Basic sanity checks before any LDAP operations even happen.
     */
    if (!sec->have_ldap_url) {
        return AUTH_GENERAL_ERROR;
    }

    /* There is a good AuthLDAPURL, right? */
    if (sec->host) {
        const char *binddn = sec->binddn;
