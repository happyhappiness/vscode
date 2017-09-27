ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Module mod_ldap missing. Mod_ldap (aka. util_ldap) "
                     "must be loaded in order for mod_auth_ldap to function properly");