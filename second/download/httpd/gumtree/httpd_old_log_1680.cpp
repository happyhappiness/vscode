ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "[%" APR_PID_T_FMT "] auth_ldap authorise: require group: "
                          "testing for group membership in \"%s\"",
                          getpid(), t);