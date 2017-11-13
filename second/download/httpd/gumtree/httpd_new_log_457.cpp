ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                              "[%d] auth_ldap authorise: checking attribute"
                              " %s has value %s", getpid(), w, value);