ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                                  "Removing LDAP connection last used %" APR_TIME_T_FMT " seconds ago",
                                  (now - l->freed) / APR_USEC_PER_SEC);