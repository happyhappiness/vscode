ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		     "proxy: error writing cache file(%s)", c->tempfile);