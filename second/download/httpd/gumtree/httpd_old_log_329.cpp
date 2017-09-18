ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
		 "proxy: CONNECT: setting up poll()");