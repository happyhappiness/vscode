ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                               "[%" APR_PID_T_FMT "] auth_ldap authorise: require group \"%s\": "
                               "failed [%s][%d - %s], checking sub-groups",
                               getpid(), t, ldc->reason, result, ldap_err2string(result));