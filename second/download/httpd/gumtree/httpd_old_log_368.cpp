ap_log_error(APLOG_MARK, APLOG_WARNING, r->server,
		    "ISAPI asynchronous I/O not supported: %s", r->filename);