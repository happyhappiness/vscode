ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
			"malformed header in meta file: %s", r->filename);