ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01712)
                          "auth_ldap authorize: require group: user's DN has "
                          "not been defined; failing authorization for user %s",
                          r->user);