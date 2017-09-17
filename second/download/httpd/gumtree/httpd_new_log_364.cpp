ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "DLL could not load GetExtensionVersion(): %s", r->filename);