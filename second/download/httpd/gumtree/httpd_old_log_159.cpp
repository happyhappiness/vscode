ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0,
		     cmd->server, "[%d] auth_ldap parse url: not requesting secure LDAP", getpid());