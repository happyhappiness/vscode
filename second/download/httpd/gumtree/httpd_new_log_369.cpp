ap_log_rerror(APLOG_MARK, APLOG_WARNING, r,
		    "ISAPI asynchronous I/O not supported: %s", r->filename);