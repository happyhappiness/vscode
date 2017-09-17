ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		     "Directory index forbidden by rule: %s", r->filename);