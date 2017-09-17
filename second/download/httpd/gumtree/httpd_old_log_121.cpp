ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server,
		"%s is not executable; ensure interpreted scripts have "
		"\"#!\" first line", 
		r->filename);