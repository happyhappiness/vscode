ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
			"malformed header in meta file: %s", r->filename);