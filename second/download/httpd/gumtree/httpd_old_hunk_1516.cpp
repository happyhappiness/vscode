    */

    /* make sure that mod_ldap (util_ldap) is loaded */
    if (ap_find_linked_module("util_ldap.c") == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Module mod_ldap missing. Mod_ldap (aka. util_ldap) "
                     "must be loaded in order for mod_auth_ldap to function properly");
        return HTTP_INTERNAL_SERVER_ERROR;

    }

    if (!charset_confname) {
        return OK;
