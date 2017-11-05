ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                    "LDAP: Could not set the LDAP library debug level to %d:(%d) %s", 
                    st->debug_level, result, ldap_err2string(result));