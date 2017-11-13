ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01706)
                              "auth_ldap authorize: "
                              "require user: authorization failed [%s][%s]",
                              ldc->reason, ldap_err2string(result));