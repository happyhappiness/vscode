ap_log_error(APLOG_MARK, APLOG_ALERT, r->server,
		    "DLL could not load HttpExtensionProc(): %s", r->filename);