ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
		 "proxy: CONNECT: connecting %s to %s:%d", url, uri.hostname, uri.port);