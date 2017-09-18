ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                              "[%d] auth_ldap authorise: "
                              "require ldap-attribute: user's DN has not been defined; failing authorisation", 
                              getpid());