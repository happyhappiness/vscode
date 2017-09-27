ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                      "[%" APR_PID_T_FMT "] auth_ldap authenticate: "
                      "user %s authentication failed; URI %s [%s][%s]",
                      getpid(), user, r->uri, ldc->reason, ldap_err2string(result));