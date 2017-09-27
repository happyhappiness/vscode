ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "util_ldap: Couldn't retrieve group entry "
                              "for %s from cache",
                              dn);