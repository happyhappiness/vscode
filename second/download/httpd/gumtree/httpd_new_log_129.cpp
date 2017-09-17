ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r,
			 "proxy: bad (short?) cache file: %s", c->filename);