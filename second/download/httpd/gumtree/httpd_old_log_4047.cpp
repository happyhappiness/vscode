ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "LDAP: LDAP_OPT_TIMEOUT option not supported by the "
                 "LDAP library in use. Using LDAPTimeout value as search "
                 "timeout only." );