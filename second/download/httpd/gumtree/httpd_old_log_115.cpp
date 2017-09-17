ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			 "Premature end of script headers: %s", r->filename);