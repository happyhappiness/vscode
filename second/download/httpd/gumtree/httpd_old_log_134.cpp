ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		     "proxy: error creating cache file %s",
		     c->tempfile);