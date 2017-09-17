ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			"File does not exist: %s", r->filename);