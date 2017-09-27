*/

    /*
     * Basic sanity checks before any LDAP operations even happen.
     */
    if (!sec->have_ldap_url) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02558) 
                      "no AuthLDAPURL");

        return AUTH_GENERAL_ERROR;
    }

    /* There is a good AuthLDAPURL, right? */
    if (sec->host) {
        const char *binddn = sec->binddn;
