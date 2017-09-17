ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		    "file permissions deny server access: %s", r->filename);