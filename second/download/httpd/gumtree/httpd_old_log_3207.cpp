ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "auth_ldap authorize: "
                              "require user: authorization failed [%s][%s]",
                              ldc->reason, ldap_err2string(result));