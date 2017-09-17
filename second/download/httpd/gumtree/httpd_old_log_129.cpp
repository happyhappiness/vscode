ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server,
			 "proxy: bad (short?) cache file: %s", c->filename);