ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "[%" APR_PID_T_FMT "] util_ldap: Couldn't "
                              "retrieve group entry for %s from cache",
                               getpid(), dn);