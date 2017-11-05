ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "[%" APR_PID_T_FMT "] auth_ldap authorize group: authorization denied for user %s to %s",
                  getpid(), r->user, r->uri);