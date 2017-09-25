ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r, 
                      "[%d] auth_ldap authorise: "
                      "no req struct - skipped mod_auth_ldap_check_user_id?",
                      getpid());