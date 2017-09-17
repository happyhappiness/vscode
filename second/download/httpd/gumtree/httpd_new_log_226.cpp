ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		     "Directory index forbidden by rule: %s", r->filename);