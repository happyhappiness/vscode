ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] util_ldap: no cached SGL for %s,"
                      " retrieving from LDAP" , getpid(), dn);