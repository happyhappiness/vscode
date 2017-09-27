ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                "auth_ldap authorise: User DN not found, %s", ldc->reason);