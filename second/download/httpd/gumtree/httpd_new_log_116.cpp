ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			 "CGI Interface Error: Script headers apparently ASCII: (CGI = %s)", r->filename);