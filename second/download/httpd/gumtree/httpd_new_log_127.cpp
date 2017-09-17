ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
			 "proxy: error opening cache file %s",
			 c->filename);