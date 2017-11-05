ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] auth_ldap authorise: require group: "
                                  "user's DN has not been defined; failing authorisation",
                                  getpid());