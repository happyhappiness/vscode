ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r->server,
				MODNAME ": bad state %d (ws)", state);