ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			    "missing expr in if statement: %s",
			    r->filename);