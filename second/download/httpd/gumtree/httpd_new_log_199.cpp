ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		  "client denied by server configuration: %s",
		  r->filename);