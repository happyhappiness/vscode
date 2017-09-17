ap_log_rerror(APLOG_MARK, show_errno|APLOG_ERR, r, 
		"%s: %s", error, r->filename);