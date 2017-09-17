ap_log_rerror(APLOG_MARK, APLOG_ALERT, r,
		    "DLL could not load HttpExtensionProc(): %s", r->filename);