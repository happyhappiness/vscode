ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		     "proxy: error setting reuseaddr option: setsockopt(SO_REUSEADDR)");