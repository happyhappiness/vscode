ap_log_error(APLOG_MARK, APLOG_ALERT, r->server,
		    "ISAPI GetExtensionVersion() failed: %s", r->filename);