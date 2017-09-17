ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
				 "proxy: error seeking on cache file %s",
				 c->filename);