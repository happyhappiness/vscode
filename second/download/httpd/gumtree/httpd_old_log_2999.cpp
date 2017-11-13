ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authorize: checking attribute"
                      " %s has value %s", getpid(), w, value);