ap_log_error(APLOG_MARK, APLOG_ALERT, r->server,
		    "Could not load DLL: %s", r->filename);