ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
				 "proxy: error seeking on cache file %s",
				 c->filename);