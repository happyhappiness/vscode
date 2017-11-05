ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] util_ldap: Cache entry "
                          "for %s doesn't exist",
                           getpid(), dn);