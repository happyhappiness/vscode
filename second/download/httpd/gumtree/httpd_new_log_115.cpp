ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			  "Premature end of script headers: %s", r->filename);