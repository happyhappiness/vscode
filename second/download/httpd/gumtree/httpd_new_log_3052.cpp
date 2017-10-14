ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "ldap connection: Setting connection timeout to %ld seconds.",
                 st->connectionTimeout);