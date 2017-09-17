ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    "Could not open password file: %s", auth_pwfile);