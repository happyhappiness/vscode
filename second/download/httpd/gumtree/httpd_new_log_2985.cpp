ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                               "auth_ldap authorise: require group \"%s\": "
                               "failed [%s][%d - %s], checking sub-groups",
                               t, ldc->reason, result, ldap_err2string(result));