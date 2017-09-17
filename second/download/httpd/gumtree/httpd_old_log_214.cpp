ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    "could not open dbm auth file: %s", auth_dbmpwfile);