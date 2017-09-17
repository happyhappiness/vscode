ap_log_rerror(APLOG_MARK, APLOG_ERR, c->req,
		 "proxy: error writing to cache file %s", c->tempfile);