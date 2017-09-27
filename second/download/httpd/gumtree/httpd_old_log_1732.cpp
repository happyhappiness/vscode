ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                      0, r, "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require ldap-filter: authorisation "
                                      "successful", getpid());