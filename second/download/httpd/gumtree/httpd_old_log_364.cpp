ap_log_error(APLOG_MARK, APLOG_ALERT, r->server,
		    "DLL could not load GetExtensionVersion(): %s", r->filename);