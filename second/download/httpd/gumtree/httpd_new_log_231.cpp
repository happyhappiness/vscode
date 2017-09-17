ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		    "couldn't spawn child process: %s", r->filename);