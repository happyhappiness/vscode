ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                              "ldap_simple_bind() timed out on reused "
                              "connection, dropped by firewall?");