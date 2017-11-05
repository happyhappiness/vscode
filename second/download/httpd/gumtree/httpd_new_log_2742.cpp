ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01716)
                               "auth_ldap authorise: require group \"%s\": "
                               "failed [%s][%d - %s], checking sub-groups",
                               t, ldc->reason, result, ldap_err2string(result));