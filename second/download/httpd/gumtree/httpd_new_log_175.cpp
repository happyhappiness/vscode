ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
		      "[%d] auth_ldap authenticate: no user specified", getpid());