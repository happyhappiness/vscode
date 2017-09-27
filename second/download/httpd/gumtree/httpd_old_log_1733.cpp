ap_log_rerror(APLOG_MARK, APLOG_DEBUG,
                                      0, r, "[%" APR_PID_T_FMT "] auth_ldap authorise: "
                                      "require ldap-filter: %s authorisation "
                                      "failed [%s][%s]", getpid(),
                                      filtbuf, ldc->reason, ldap_err2string(result));