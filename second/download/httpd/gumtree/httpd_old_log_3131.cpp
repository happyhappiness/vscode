ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "[%" APR_PID_T_FMT "] util_ldap:"
                                  " Making local copy of SGL for "
                                  "group (%s)(objectClass=%s) ",
                                  getpid(), dn,
                                  (char *)sgc_ents[base_sgcIndex].name);