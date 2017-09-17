ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			 "proxy: error reading cache file %s", 
			 c->filename);