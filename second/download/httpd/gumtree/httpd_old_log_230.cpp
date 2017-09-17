ap_log_error(APLOG_MARK, show_errno|APLOG_ERR, r->server, 
		"%s: %s", error, r->filename);