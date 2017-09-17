ap_log_error(APLOG_MARK, APLOG_ERR, c->req->server,
		 "proxy: error writing to cache file %s", c->tempfile);