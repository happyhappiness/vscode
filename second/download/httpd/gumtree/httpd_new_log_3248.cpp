ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01747)
                              "auth_ldap authorize: require ldap-filter: "
                              "authorization failed [%s][%s]",
                              ldc->reason, ldap_err2string(result));