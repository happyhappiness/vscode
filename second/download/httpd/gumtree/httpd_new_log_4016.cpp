ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01284)
                          "ldap_simple_bind() timed out on %s "
                          "connection, dropped by firewall?",
                          new_connection ? "new" : "reused");