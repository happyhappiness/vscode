ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01727)
                          "auth_ldap authorize: "
                          "require dn \"%s\": LDAP error [%s][%s]",
                          t, ldc->reason, ldap_err2string(result));