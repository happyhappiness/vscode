ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                 "[%" APR_PID_T_FMT "] ldap connection: Setting op timeout "
                 "to %ld seconds.", getpid(), timeout);