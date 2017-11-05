ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01719)
                              "auth_ldap authorize: require group \"%s\": "
                              "authorization failed [%s][%d - %s]",
                              t, ldc->reason, result, ldap_err2string(result));