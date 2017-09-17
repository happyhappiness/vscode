ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
			 "proxy: error reading cache file %s", 
			 c->filename);