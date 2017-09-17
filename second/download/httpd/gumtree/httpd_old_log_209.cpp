ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    "could not open db auth file: %s", auth_dbpwfile);