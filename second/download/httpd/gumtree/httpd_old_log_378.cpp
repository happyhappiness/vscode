ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, r,
			 "proxy: %s returned by %s", message, r->uri);