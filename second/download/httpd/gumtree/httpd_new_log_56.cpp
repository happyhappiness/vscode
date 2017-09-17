ap_log_rerror(APLOG_MARK, APLOG_CRIT, r,
			 "default_handler: mmap failed: %s", r->filename);