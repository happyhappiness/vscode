ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
                                  "[%d] auth_ldap authorise: "
                                  "require dn \"%s\": LDAP error [%s][%s]",
                                  getpid(), t, ldc->reason, ldap_err2string(result));