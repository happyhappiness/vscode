ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "ISAPI GetExtensionVersion() failed: %s", r->filename);