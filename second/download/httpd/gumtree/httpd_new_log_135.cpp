ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
		     "proxy: error writing cache file(%s)", c->tempfile);