ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    "couldn't spawn child process: %s", r->filename);