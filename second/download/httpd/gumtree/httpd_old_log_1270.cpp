ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: attrib: %s", getpid(), urld->lud_attrs? urld->lud_attrs[0] : "(null)");