ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			     "fread of %s failed", r->filename);