ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "Could not load DLL: %s", r->filename);